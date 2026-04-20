findFact() {
    local n=$1
    local fact=1

    for ((i=1; i<=n; i++)); do
        fact=$((fact * i))
    done

    echo $fact
}

nPr() {
    local n=$1
    local r=$2

    if [ $r -gt $n ] || [ $n -lt 0 ] || [ $r -lt 0 ]; then
        echo 0
        return
    fi

    local n_fact=$(findFact $n)
    local nr_fact=$(findFact $((n - r)))

    echo $((n_fact / nr_fact))
}

read -p "Enter n: " n
read -p "Enter r: " r

echo "P($n, $r) = $(nPr $n $r)"