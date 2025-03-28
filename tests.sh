touch infile_bash outfile_bash infile_pipex outfile_pipex

echo "aaa\naaa" > infile_bash
echo "aaa\naaa" > infile_pipex

diff outfile_bash outfile_pipex

# test1
< infile_bash cat | wc > outfile_bash
./pipex infile_pipex cat wc outfile_pipex

# test2
< infile_bash cat | wc -l > outfile_bash
./pipex infile_pipex cat "wc -l" outfile_pipex

# test3
< infile_bash sleep 3 | wc -l > outfile_bash
echo $?

./pipex infile_pipex "sleep 3" "wc -l" outfile_pipex
echo $?

# test4
< infile_bash qwertyuiop | wc -l > outfile_bash
echo $?

./pipex infile_pipex qwertyuiop "wc -l" outfile_pipex
echo $?

# test5
< infile_bash cat | grep aaa > outfile_bash
./pipex infile_pipex cat "grep aaa" outfile_pipex

# test6
< infile_bash cat | grep bbb > outfile_bash
echo $?

./pipex infile_pipex cat "grep bbb" outfile_pipex
echo $?

# test7
< infile_bash cat | qwertyuiop > outfile_bash
echo $?

./pipex infile_pipex cat "qwertyuiop" outfile_pipex
echo $?

# test8
< infile_bash cat | /bin/wc > outfile_bash
./pipex infile_pipex cat "/bin/wc" outfile_pipex

# test9
< infile_bash cat | /bin/wc -l > outfile_bash
./pipex infile_pipex cat "/bin/wc -l" outfile_pipex

# test10
< infile_bash grep bbb | wc > outfile_bash
echo $?

./pipex infile_pipex "grep bbb" wc outfile_pipex
echo $?

# test11
chmod 000 infile_bash
chmod 000 infile_pipex
< infile_bash cat | wc > outfile_bash
echo $?

./pipex infile_pipex cat wc outfile_pipex
echo $?
chmod 666 infile_bash
chmod 666 infile_pipex

# test12
chmod 000 outfile_bash
chmod 000 outfile_pipex
< infile_bash cat | wc > outfile_bash
echo $?

./pipex infile_pipex "cat" wc outfile_pipex
echo $?
chmod 666 outfile_bash
chmod 666 outfile_pipex

# test13
chmod 000 infile_bash
chmod 000 infile_pipex
chmod 000 outfile_bash
chmod 000 outfile_pipex
< infile_bash cat | wc > outfile_bash
echo $?

./pipex infile_pipex "cat" wc outfile_pipex
echo $?
chmod 666 infile_bash
chmod 666 infile_pipex
chmod 666 outfile_bash
chmod 666 outfile_pipex

# test14
./pipex infile_pipex cat wc

# test15
unset PATH
< infile_bash cat | wc > outfile_bash
echo $?

./pipex infile_pipex cat wc outfile_pipex
echo $?

# test16
< infile_bash ls -l | wc -l > outfile_bash
./pipex infile_pipex "ls -l" "wc -l" outfile_pipex

# test17
< infile_bash grep a1 | wc -w > outfile_bash
./pipex infile_pipex "grep a1" "wc -w" outfile_pipex