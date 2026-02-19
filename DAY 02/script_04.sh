read -p "Are you an Admin? (y/n): " isAdmin
read -p "Are you a Moderator (y/n): " isModerator
if [ "$isAdmin" == "y" ] || [ "$isModerator" == "y" ]; then
echo "You have special privileges"
else
echo "You don't have special privileges"
fi