
#include <iostream>
#include <random>

using std::cout;
using std::endl;

class Zufall
{
public:

    static int random(int min, int max) {
      
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(min, max);

  /*  for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {*/
       //cout << distr(eng) << "; ";
        return distr(eng);
   /* }*/
    //cout << endl;

    }

};






