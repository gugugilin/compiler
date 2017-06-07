name=$1
IFS='/' read -r -a array <<< "$name"
len=${#array[@]}
IFS='.' read -r -a array <<< "${array[$len-1]}"
./a1.out $name > "${array[0]}.jasm"
./javaa/javaa "${array[0]}.jasm"
java ${array[0]}

