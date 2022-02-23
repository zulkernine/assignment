for ((i=1;i<=10;i++));do
    ((m=i*$1))
    echo "$i * $1 = $m"
done
