if g++ main.cpp network.cpp -o main.out -lGL -lGLU -lglut; then
echo "Compilation successful. Executing ...";
./main.out

else
echo "Compilation failed";
fi
