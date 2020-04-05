#include "network.h"
#include <iostream>
#include <vector>
#include <random>
#include <bits/stdc++.h>

const int field_height = 20 + 2;
const int field_width = 20 + 2;

int step;

int field[field_width][field_height] = {0};
double surroundings[4] = {0};
int position[2] = {1, 1};

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

int median(std::vector<double> steps_in){

  std::vector<double> stepsmed;

  for(int x = 0; x < steps_in.size(); x++){
    stepsmed.push_back(steps_in[x]);
  }

  std::sort(stepsmed.begin(), stepsmed.end());


  return stepsmed[stepsmed.size() / 2];

}

int main(int argc, char **argv){

  int population_size = 500;

  std::vector<Network> networks;
  std::vector<double> steps;

  int maxstep = -1;
  Network n1(4, 1, 4, 4); //initial network

  for(int x = 0; x < population_size; x++){
    n1.mutate(20);
    networks.push_back(n1);
    steps.push_back(1);
  }

  int iter_num = 1;
  while (true){

      //get median

      int avgsteps = median(steps);

      //output iteration number
      if(iter_num % 10 == 0){
        std::cout << "==================\n";
        std::cout << "Iteration number: " << iter_num << std::endl;
        std::cout << "Population size: " << networks.size() << std::endl;
        std::cout << "Average steps: " << avgsteps << std::endl;


      }

      iter_num += 1;

      // for each network
      for(int x = 0; x < networks.size(); x++){

          if(steps[x] <= avgsteps && networks.size() > population_size / 2){

              networks.erase(networks.begin() + x);
              steps.erase(steps.begin() + x);

              x = x - 1;

          }else if(networks.size() < population_size*2){

            Network n2(4, 1, 4, 4);

            if(randDouble() > 0.2){
              n2 = networks[x];
            }


            n2.mutate(20);
            n2.mutate(20);
            n2.mutate(20);
            n2.mutate(20);
            n2.mutate(20);
            n2.mutate(20);


            //prepare field
            resetField();
            int direction =  1;
            field[1][1] = 2;
            snake.clear();
            snake.push_back({1, 1});

            int alive = 1;
            step = 0;

            while (alive == 1){
              step = step + 1;

              getposition();
              whatsaround(position[0], position[1]);

              n2.set_input_nodes(surroundings);
              n2.forward_propagate();

              std::vector<double> out = n2.output_nodes;

              double maxout = -1;
              int maxpos = -1;

              for(int n = 0; n < 4; n++){
                if(out[n] > maxout){
                  maxout = out[n];
                  maxpos = n;
                }
              }

              alive = move(maxpos + 1);

            }

            networks.push_back(n2);
            steps.push_back(step);

            if(maxstep < step){
              n2.save("saved.AI");
              maxstep = step;
              std::cout << "\033[32mImprovement: " << maxstep << "\033[0m" << std::endl;
            }
          }

      }
  }
}
