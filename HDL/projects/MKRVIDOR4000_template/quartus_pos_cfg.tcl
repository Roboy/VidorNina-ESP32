qexec "quartus_cpf -c out_cfg.cof"
qexec "quartus_cpf -c out_cfg0.cof"

set fh_input [open outputfile.ttf]
set fh_out [open app.h w]
set line_num 1

set buffer_char 0
#set filtered_string_data 0

set flag_kill [gets $fh_input line]

while { $flag_kill >= 0 } {
    #remove spaces and special chars
    set raw_data [string map {" " ""} $line]
    set raw_data [string map {"\n" ""} $raw_data]
    set raw_data [string map {"\r" ""} $raw_data]
    set raw_data [string map {"\t" ""} $raw_data]
    set raw_data [string map {" " ""} $raw_data]
    set n [split $raw_data ","]

    set i 0
    set filtered_string_data {}
    while { [llength $n] > [expr $i + 1]} {

      set source [lindex $n $i]
      set result 0
      set source_buffer 0

      set source_test [lindex $n 2]

      if { $source == "" } {
        #puts $fh_out "FUCKING TCL"
      } else {
        for { set j 0 } { $j < 8 } { incr j } {
          set result [expr $result >> 1]
          set source_buffer [expr $source & 0x80]

          if { $source_buffer == 0x80 } {
            #format 0x%x [expr {0xa + 0xa}]  ;# ==> 0x14
            set result [expr {$result + 0x80}]
          }

          set source [expr $source << 1]
        }
      }

      #if($i [expr [llength $n] + 2] )
      lappend filtered_string_data $result

      incr i
    }

    #put the line back together
    set line_output [join $filtered_string_data ","]


    incr line_num

    set flag_kill [gets $fh_input line]

    if { $flag_kill >= 0} {
      puts $fh_out "$line_output,"
    } else {
      puts -nonewline $fh_out "$line_output,"
    }
}
puts -nonewline $fh_out "255,"

close $fh_input
close $fh_out

file copy -force app.h ../../../software/vidorSAM/app.h



#puts $fh [join $row_data ","]
