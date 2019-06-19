
count=1
while(($count<50))
do
    ./main
#     sleep 0.1
    count=$(($count+1))
#     count=`expr $count + 1`
#     let count+=1
    echo $count
done
