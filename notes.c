/*
* Cat and ^c should be treat 
* 
* [X] Prob find first how many pipes "|" i got on cmd_line and separate by how many t_cmd structure i'll have
* [X] Maybe add a boolean logic to clean all address inside struct data but keep variable of history safe?
* [X] command cat > file4 ( which doest not exist) get stuck on terminal
* [] I still need to treat the case of ls | which my parsing return error_handling but need to go to here_doc
* [] in a command order if theres <<, i need to priority HERE_DOC at all, after here doc I make any commands
* [] Need to add header files into pre-dependence on Makefile 
* [] Need to treat exit status
* [] Nees to test exit status on here_doc
* [] Need to check file handle_folders, with error ze told on zap :)
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

when i end with ^d
hbourlot@c65c2c36c642:~/Projects/minishell_42$ << eof
>
bash: warning: here-document at line 10 delimited by end-of-file (wanted `eof')
hbourlot@c65c2c36c642:~/Projects/minishell_42$


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


// •	Read (r) = 4
// •	Write (w) = 2
// •	Execute (x) = 1
// 0644
// Owner: rw-   (Read + Write)
// Group: r--   (Read only)
// Others: r--  (Read only)
// 0777
// Owner: rwx   (Read + Write + Execute)
// Group: rwx   (Read + Write + Execute)
// Others: rwx  (Read + Write + Execute)



// echo oi > file | exit > l
// exit > l


//* Only tokens commands
// > file
// >> file
// << file
// < file
// <
// >
// > file



// TESTS
// << eof
// << eof "
// << eof " |
// << eof " | "
// << eof " | " |
// << eof " | " | ls
// << eof |||
// << eof | |
// << eof + ^d
// << eof + ^d | ls
// << eof <<"eof1 " "<<" <<'eof 3' <<" eof4 " <<eof5
//* echo "File creation madness" > "file_>_and_|.txt" | cat "file_>_and_|.txt" ">>" pegadinha_do_malandro | grep "madness"
