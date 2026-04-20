read -p "Enter a number: " num

findFact() {
    local n=$1
    local fact=1

    while [ $n -gt 1 ]; do
        fact=$((fact * n))
        n=$((n - 1))
    done

    echo $fact
}

result=$(findFact $num)
echo "Factorial of $num is: $result"

nCr() {
    local n=$1
    local r=$2

    if [ $r -gt $n ] || [ $n -lt 0 ] || [ $r -lt 0 ]; then
        echo 0
        return
    fi

    local n_fact=$(findFact $n)
    local r_fact=$(findFact $r)
    local nr_fact=$(findFact $((n - r)))

    echo $((n_fact / (r_fact * nr_fact)))
}

read -p "Enter n for combination (nCr): " n
read -p "Enter r for combination (nCr): " r

ncr_result=$(nCr $n $r)
echo "C($n, $r) = $ncr_result"Copied!