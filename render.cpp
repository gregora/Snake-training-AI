#include "network.h"
#include "simple2D.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>


const int field_height = 20 + 2;
const int field_width = 20 + 2;

int step;

int field[field_width][field_height] = {0};
double surroundings[4] = {0};
int position[2] = {5, 5};

std::vector<std::vector<int>> snake;

extern int window_width;
extern int window_height;


double randDouble(){
  std::random_device rd{};
  std::mt19937 engine{rd()};
  std::uniform_real_distribution<double> dist{0.0, 1.0};
  double ret = dist(engine);
  return ret;
}

void renderField(){

  for(int y = 0; y < field_height; y++){
    for(int x = 0; x < field_width; x++){
      std::cout << field[x][y] << " ";
    }
    std::cout << "\n";
  }

}

int move(int direction){

  for(int x = 0; x < field_width; x++){
    for(int y = 0; y < field_height; y++){
      if(field[x][y] == 2){

        field[x][y] = 1;
        snake.push_back({x, y});

        double ran = randDouble();

        if(step % 5 != 0){

          field[snake[0][0]][snake[0][1]] = 0;
          snake.erase(snake.begin());

        }


        if(direction == 1){

            if(field[x + 1][y] == 0){
              field[x + 1][y] = 2;
            }else{
              return 0;
            }

        }else if(direction == 3){

            if(field[x - 1][y] == 0){
              field[x - 1][y] = 2;
            }else{
              return 0;
            }

        }else if(direction == 2){

            if(field[x][y - 1] == 0){
              field[x][y - 1] = 2;
            }else{
              return 0;
            }

        }else if(direction == 4){

            if(field[x][y + 1] == 0){
              field[x][y + 1] = 2;
            }else{
              return 0;
            }

        }
        return 1;
        break;
      }
    }
  }


}

void getposition(){
  for(int x = 0; x < field_width; x++){
    for(int y = 0; y < field_height; y++){
        if(field[x][y] == 2){
          position[0] = x;
          position[1] = y;
        }
    }
  }
}

void whatsaround(int x, int y){

  /*int c = 0;

  for(int x = 0; x < field_width; x++){
    for(int y = 0; y < field_height; y++){

      surroundings[c] = field[x][y];

      c+=1;

    }
  }*/

  surroundings[0] = field[x + 1][y];
  surroundings[1] = field[x][y + 1];
  surroundings[2] = field[x - 1][y];
  surroundings[3] = field[x][y - 1];

}

void resetField(){

  for(int y = 0; y < field_height; y++){
    for(int x = 0; x < field_width; x++){
      if(x!=0 && y!=0 && x!=field_width - 1 && y!=field_height - 1){
        field[x][y] = 0;
      }else{
        field[x][y] = 3; //create border
      }
    }
  }


}

int main(int argc, char **argv){

  std::string filename;

  std::cout << "Filename: ";
  std::cin >> filename;

  Network n1(4, 1, 4, 4);
  n1.load(filename);


  resetField();
  int direction =  1;
  field[1][1] = 2;

  snake.clear();
  snake.push_back({1, 1});

  int alive = 1;

  int steps2 = 0;

  std::string a;

  start(argc, argv, field_width*30, field_height*30, "test");

  step = 0;

  while (alive == 1){

    std::this_thread::sleep_for (std::chrono::milliseconds(20));

    step = step + 1;
    getposition();
    whatsaround(position[0], position[1]);

    n1.set_input_nodes(surroundings);
    n1.forward_propagate();

    std::vector<double> out = n1.output_nodes;

    double maxout = -1;
    int maxpos = -1;

    for(int n = 0; n < 4; n++){
      if(out[n] > maxout){
        maxout = out[n];
        maxpos = n;
      }
    }

    alive = move(maxpos + 1);

    rerender();

  }

  std::cout << step << std::endl;



}

void render(double delta){

  for(int x = 0; x < field_width; x++){
    for(int y = 0; y < field_height; y++){

      int curr_tile = field[x][field_height - 1 - y];

      if(curr_tile == 1){
        setColor(1, 0, 0);
      }else if(curr_tile == 2){
        setColor(0, 1, 0);
      }else if(curr_tile == 0){
        setColor(1, 1, 1);
      }else{
        setColor(0, 0, 1);
      }

      rectangle(x*30 - window_width / 2, y*30 - window_height / 2, x*30 + 30 - window_width / 2, y*30 + 30 - window_height / 2);

    }

  }

  setColor(0, 0, 0);

  text(- (window_width / 2) + 40,  (window_height / 2) - 50, GLUT_BITMAP_HELVETICA_18, std::to_string(step));

}

void keyboardInput(unsigned char k, int x, int y){}
