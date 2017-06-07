name=$1
IFS='/' read -r -a array <<< "$name"
len=${#array[@]}
if [ $len -gt 0 ];then
IFS='.' read -r -a array <<< "${array[$len-1]}"
len=${#array[@]}
echo ${array[1]}
if [ $len -gt 1 ];then
    if [ "${array[1]}"=="go" ];then
        ./a1.out $name > "${array[0]}.jasm"
        ./javaa/javaa "${array[0]}.jasm"
        java ${array[0]}
    else
        echo "must be a go file"
    fi
else
    echo "argument error"
fi
else
    echo "argument error"
fi
