read -p "Enter player name: " player
echo "Length of the name is: ${#player}"
read -p "Enter number of matches played: " num

totalRuns=0
highestScore=0
halfCenturies=0
runsList=()

for(( i=0; i<num; i++ ));
do
    read -p "Enter runs for match no. $i: " runs
    runsList+=$(( totalRuns + runs ))

    if (( runs >= 50 )); then
        halfCenturies+=$((halfCenturies + 1))
    fi

    if (( runs >= highestScore )); then
        highestScore=$runs
    fi
done

if (( num > 0 )); then
    averageRuns=$((totalRuns / num))
else
    averageRuns=0
fi

echo "Total Runs: $totalRuns"
echo "Average Runs: $averageRuns"
echo "Highest Score: $highestScore"
echo "Number of half centuries: $halfCenturies"

performance=""
if (( averageRuns >= 50 )); then
    performance="Excellent"
elif (( averageRuns >= 30 )); then
    performance="Good"
elif (( averageRuns >= 10 )); then
    performance="Average"
else
    performance="Poor"
fi

echo "Performance: $performance"