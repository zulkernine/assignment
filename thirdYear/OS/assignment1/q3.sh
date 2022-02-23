count=0
while read line;do
    ((count+=1))
done < $1
((count++))
echo "Number of lines $count"
