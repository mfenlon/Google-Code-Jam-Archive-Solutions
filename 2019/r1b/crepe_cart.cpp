//Manhattan Crepe Cart can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/0000000000051706/000000000012295c

#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);  //allows C++ i/o streams to buffer independently from C streams
  cin.tie(0); //cin does not wait for cout to flush
  int t; cin >> t; //read number of test cases
  for(int i=0;i<t;++i){ //for each test case:
    int p,q; cin >> p >> q; //read number of people and dimension grid
    map<int,pair<int,int>> xcoords; //tracks number of people at each x and y coordinate, respectively
    map<int,pair<int,int>> ycoords; ////the first int in the pair represents how many people at the coordinate are going E or N, respectively
                                    ////the second int in the pair represents how many people at the coordinate are going W or S, respectively
                                    ////the formats are <C,<N,S>> and <C,<E,W>>
    int w=0; int s=0; //will tell us how many people in total are headed W and how many are headed S
    for(int j=0;j<p;++j){  //for each person:
      int x,y; //x and y coordinate at which they are standing
      string d;  //direction in which the person is headed
      cin >> x >> y >> d; //read person info
      if(d=="W") ++w;  //increment W or S counter if appropriate
      else if (d=="S") ++s;
      if(xcoords.find(x)!=xcoords.end()){ //if there is somebody at the x coordinate already:
        if(d=="E") ++(xcoords[x].first); //increment E or W
        else if(d=="W") ++(xcoords[x].second);
      }
      else{      //if there is nobody at the current coordinate already:
        if(d=="E") xcoords[x].first=1; //set E or W equal to 1
        else if(d=="W") xcoords[x].second=1;
      }
      if(ycoords.find(y)!=ycoords.end()){ //if there is somebody at the y coordinate already:
        if(d=="N") ++(ycoords[y].first); //increment E or W
        else if(d=="S") ++(ycoords[y].second);
      }
      else{    //if there is nobody at the current coordinate already:
        if(d=="N") ycoords[y].first=1; //set N or S equal to 1
        else if(d=="S") ycoords[y].second=1;
      }
    }
    /********
    * Now that we know where everybody is and where everybody is going,
    * we can determine which coordinate in the x has the most people
    * headed towards it and which coordinate in the y has the most people
    * headed towards it. Start at (0,0):
    *********/
    int xcart=0;
    int ycart=0;

    //The number of people headed towards (0,0) is equal to the number
    //of people headed W and the number of people headed S.
    //Keep track of the greatest number of people headed to the current coordinate.

    int xcur=w;
    int ycur=s;
    int xmost=xcur;
    int ymost=ycur;

    //Traverse along the x and up the y, checking if the number
    //of people headed to the new coordinate is greater than the
    //number of people headed to the current leading coordinate.
    //The coordinates that we will check in the x are any
    //coordinates to the right of a person. The coordinates that
    //we will check in the y are any coordinates above a person.
    //The equation for determining the number of people to headed
    //toward a given coordinate is as follows:
    //xcur = xcur - xcur(W) + xcur(E) - xcur+1(W)
    //where xcur(W) and xcur(E) are the number of people at the
    //current coordinate headed W and E.

    map<int,pair<int,int>>::iterator xit=xcoords.begin();
    map<int,pair<int,int>>::iterator yit=ycoords.begin();
    while(xit!=xcoords.end() || yit!=ycoords.end()){
      if(xit!=xcoords.end()){
        xcur=xcur-(xit->second).second+(xit->second).first;
        map<int,pair<int,int>>::iterator nxit=next(xit);
        if(nxit!=xcoords.end() && nxit->first==xit->first+1) xcur-=(nxit->second).second;
        if(xcur>xmost){
          xmost=xcur;
          xcart=(xit->first)+1;
        }
        if(nxit!=xcoords.end() && nxit->first==xit->first+1) xcur+=(nxit->second).second;
        ++xit;
      }
      if(yit!=ycoords.end()){
        ycur=ycur-(yit->second).second+(yit->second).first;
        map<int,pair<int,int>>::iterator nyit=next(yit);
        if(nyit!=ycoords.end() && nyit->first==yit->first+1) ycur-=(nyit->second).second;
        if(ycur>ymost){
          ymost=ycur;
          ycart=(yit->first)+1;
        }
        if(nyit!=ycoords.end() && nyit->first==yit->first+1) ycur+=(nyit->second).second;
        ++yit;
      }
    }

    //Congrats! You did it! Let 'em know!
    cout << "Case #" << i+1 << ": " << xcart << ' ' << ycart << endl;
  }
}