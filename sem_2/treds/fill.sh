for N in 100 500 1000; do
  for t in 1 2; do
    ./a.out $N $t
  done
done

for N in 100 500 1000 1500 2000;do
  for t in 4 6 8 16; do
    ./a.out $N $t
  done
done
