/* 
* [X] Prob find first how many pipes "|" i got on cmd_line and separate by how many t_cmd structure i'll have
* [X] Maybe add a boolean logic to clean all address inside struct data but keep variable of history safe?
* [] in a command order if theres <<, i need to priority HERE_DOC at all, after here doc I make any commands
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*/


// +---------------------------+
// | Text Segment              | <-- Stores code (read-only)
// +---------------------------+
// | Data Segment              | <-- Stores initialized global/static variables
// +---------------------------+
// | BSS Segment               | <-- Stores uninitialized global/static variables
// +---------------------------+
// | Heap                      | <-- Grows upwards, for dynamic allocation
// +---------------------------+
// | Stack                     | <-- Grows downwards, for local variables
// +---------------------------+