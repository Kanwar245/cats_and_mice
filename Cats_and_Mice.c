/*
  UTSC - CSC B63 Winter 2012

  This is the implemnentation file for the module that provides
  functionality to the cats and mouse.

  You will need to be familiar with the functions
  provided by

  graph_management.h
  GameAI.h

  and your own
  graph_algorithms.[h,c]

  You must complete *ALL* sections marked "TO DO". Please make
  sure your code works as expected and follow all instructions
  provided in the handout as well as in the comments included
  in this file.

  Places marked "CRUNCHY" are extra credit.

  F.J.E. March 2012
*/

#include "Cats_and_Mice.h"

struct path_node *kittyEyeWalk(int GamePos[numAgents][3], float A[GsizeSqr][GsizeSqr], int kitty)
{
 /*
   Kitty walk based on vision. The expected behaviour is as follows:

   If the mouse is visible to the cat (aligned horizontally or
   vertically, *with no walls in between*), the kitty will move
   toward the mouse.

   Otherwise, the kitty will choose randomly from available
   neighbours.

   With this function as with all others you should make sure
   we do not get any 'phantom cats' walking through walls!

   Note this function should return a *single* node path with
   the next position for the corresponding kitty.
 */

 struct path_node *path=NULL;
 int mouse_x =  GamePos[1][0], mouse_y = GamePos[1][1], kitty_x = GamePos[kitty][0], kitty_y = GamePos[kitty][1];
 int A_kitty = kitty_x + Gsize*kitty_y;		/*position of kitty in A*/
 /*positions of kitty's neighbors in A*/
 int top = Gsize*(kitty_y-1) + kitty_x, bot = Gsize*(kitty_y+1) + kitty_x, left = Gsize*kitty_y + kitty_x-1, right = Gsize*kitty_y + kitty_x+1;
 int i, flag = 0;	/*flag is used for wall*/
 
 /*check for vertical walls when kitty is below mouse*/
 if (kitty_y < mouse_y && mouse_x == kitty_x) {
 	for(i = kitty_y; i < mouse_y; i++) {	
		if (!A[i*Gsize+kitty_x][(i+1)*Gsize+kitty_x]) { 	
			flag = 1;		/*there is wall*/
			break;
		}
	}
	if (!flag) 		/*no wall*/
		return path = newPathNode(kitty_x, kitty_y+1);	/*move to top*/
 }
 /*check for vertical walls when kitty is above mouse*/
 else if (kitty_y > mouse_y && kitty_x == mouse_x) {
	for(i = mouse_y; i < kitty_y; i++) {
		if (!A[i*Gsize+mouse_x][(i+1)*Gsize + mouse_x]) {
			flag = 1;	/*there is wall*/
			break;
		}
	}
	if (!flag)		/*no wall*/
		return path = newPathNode(kitty_x, kitty_y-1);	/*move to bottom*/
 }

 /*check for horizontal walls when kitty is on the left of mouse*/
 else if (kitty_x < mouse_x && mouse_y == kitty_y) {
 	for(i = kitty_x; i < mouse_x; i++) {	
		if (!A[kitty_y*Gsize+i][kitty_y*Gsize+i+1]) {
			flag = 1;	/*there is wall*/
			break;
		}
	}
	if (!flag)		/*no wall*/
		return path = newPathNode(kitty_x+1, kitty_y);	/*move to right*/
 }
 /*check for horizontal walls when kitty is on the right of mouse*/
 else if (kitty_x > mouse_x && kitty_y == mouse_y) {
	for(i = mouse_x; i < kitty_x; i++) {
		if (!A[mouse_y*Gsize+i][mouse_y*Gsize+i+1]) {
			flag = 1; 	/*there is wall*/
			break;
		}
	}
	if (!flag)		/*no wall*/
		return path = newPathNode(kitty_x-1, kitty_y);	/*move to left*/
 }
 else {						/*randomly go to any of the four neighbours*/
	int num = rand()%4+1;	/*randomly selects a number between 1 and 4*/ 	switch(num) {
			case 1:							/*move to left neighbour*/
				if (A[left][A_kitty] && kitty_x-1 >= 0)	/*if no wall*/
					path = newPathNode(kitty_x-1, kitty_y);
					break;
			case 2:							/*move to right neighbour*/
				if (A[right][A_kitty] && kitty_x+1 < Gsize)		/*if no wall*/
					path = newPathNode(kitty_x+1, kitty_y);
					break;
			case 3:								/*move to top neighbour*/
				if (A[top][A_kitty] && kitty_y-1 >= 0)	/*if no wall*/
					path = newPathNode(kitty_x, kitty_y-1);
					break;
			case 4:								/*move to bottom neighbour*/
		 		if (A[bot][A_kitty] && kitty_y+1 < Gsize)	/*if no wall*/	
					path = newPathNode(kitty_x, kitty_y+1);
					break;
		}
 }
 return(path);
}

struct path_node *kittySmellWalk(int GamePos[numAgents][3], float A[GsizeSqr][GsizeSqr], int kitty)
{
 /*
   Kitty walk based on smell. Expected behaviour:

   The kitties don't know where the mouse is, but they can use 'smell' to determine whether
   neighboring positions in the grid are closer or farther away from the mouse.

   The kitties will move in whichever valid direction minimizes distance to the mouse.
   If two directions result in the same distance, choose either.

   All distances are Manhattan distances.

   Kitties can get stuck... to un-stick them, see kittySmartSmell()
 */

 struct path_node *path = NULL;
 int mouse_x = GamePos[1][0], mouse_y = GamePos[1][1], kitty_x = GamePos[kitty][0], kitty_y = GamePos[kitty][1];	/*mouse's and kitty's positions*/
 int top, bot, left, right, dist;		/*possible positions where the kitty can move*/

 int A_kitty = Gsize*kitty_y + kitty_x;		/*position of kitty in A*/
 /*positions of kitty's neighbors in A*/
 top = Gsize*(kitty_y-1) + kitty_x, bot = Gsize*(kitty_y+1) + kitty_x, left = Gsize*kitty_y + kitty_x-1, right = Gsize*kitty_y + kitty_x+1;
 
 /*find the manhattan distance for all four neghbours*/
 int dist_top = abs(kitty_x-mouse_x) + abs((kitty_y-1)-mouse_y);
 int dist_bot = abs(kitty_x-mouse_x) + abs((kitty_y+1)-mouse_y);
 int dist_left = abs((kitty_x-1)-mouse_x) + abs(kitty_y-mouse_y);
 int dist_right = abs((kitty_x+1)-mouse_x) + abs(kitty_y-mouse_y);
 
 /*now check to see which one is the min distance that was just found*/
 /*top is min*/
 if (dist_top <= dist_bot && dist_top <= dist_left && dist_top <= dist_right) {
	if (A[A_kitty][top] && kitty_y-1 >= 0)
		return path = newPathNode(kitty_x, kitty_y-1);
 }
 /*bot is min*/
 if (dist_bot <= dist_top && dist_bot <= dist_left && dist_bot <= dist_right) {
 	if (A[A_kitty][bot] && kitty_y+1 < Gsize)
	 	return path = newPathNode(kitty_x, kitty_y+1);
 }
 /*left is min*/
 if (dist_left <= dist_bot && dist_left <= dist_top && dist_left <= dist_right) {
 	if (A[A_kitty][left] && kitty_x-1 >= 0)
 		return path = newPathNode(kitty_x-1, kitty_y);
 }
 /*right is min*/
 if (dist_right <= dist_bot && dist_right <= dist_left && dist_right <= dist_top) {
 	if (A[A_kitty][right] && kitty_x+1 < Gsize)
 		return path = newPathNode(kitty_x+1, kitty_y);
 }
 /*there is wall, kitty is stuck*/
 return path = newPathNode(kitty_x, kitty_y);
}

struct path_node *kittySmartSmell(int GamePos[numAgents][3], float A[GsizeSqr][GsizeSqr], int Target[numAgents][2], int kitty)
{
 /*
   Kitty walk using smart smell. Expected behaviour:

   As long as the kitty is not stuck, it uses smell just like the kittySmellWalk()
   function (in fact, you're allowed to call that function from here if you
   like).

   A kitty that has reached a dead end is allowed to use the shortest path
   algorithm to find the best route to go to the other side of whichever
   wall is blocking it.

   Once the cat switches to shortest-path, it MUST reach the intended target
   destination.

   After the kitty has arrived at its intended destination, it reverts to
   using smell to track the mouse.
 */

 struct path_node *path=NULL;
 int mouse_x = GamePos[1][0], mouse_y = GamePos[1][1], kitty_x = GamePos[kitty][0], kitty_y = GamePos[kitty][1];
 int A_kitty = kitty_x + kitty_y*Gsize;		/*position of kitty in A*/
 path = newPathNode(kitty_x, kitty_y);	/*current position*/
 
 /*find the manhattan distance for all four neghbours*/
 int dist_top = abs(kitty_x-mouse_x) + abs((kitty_y-1)-mouse_y);
 int dist_bot = abs(kitty_x-mouse_x) + abs((kitty_y+1)-mouse_y);
 int dist_left = abs((kitty_x-1)-mouse_x) + abs(kitty_y-mouse_y);
 int dist_right = abs((kitty_x+1)-mouse_x) + abs(kitty_y-mouse_y);

 /*target not set*/
 struct path_node *smell;
 if(-1 == Target[kitty][0] && -1 == Target[kitty][1]) {
 	smell = kittySmellWalk(GamePos, A, kitty);		
	/*kitty is not stuck*/
 	if (!(path->x == smell->x) && !(path->y == smell->y))
		return smell;	
	else {	/*kitty is stuck*/
		if (dist_top <= dist_bot && dist_top <= dist_right && dist_top <= dist_left) {
			/*update target*/
			Target[kitty][0] = kitty_x;
			Target[kitty][1] = kitty_y-1;
		}
		else if (dist_bot <= dist_top && dist_bot <= dist_left && dist_bot <= dist_right) {
			/*update target*/
			Target[kitty][0] = kitty_x;
			Target[kitty][1] = kitty_y+1;
		}
		else if (dist_right <= dist_top && dist_right <= dist_bot && dist_right <= dist_left) {
			/*update target*/
			Target[kitty][0] = kitty_x+1;
			Target[kitty][1] = kitty_y;
		}
		else if (dist_left <= dist_top && dist_left <= dist_bot && dist_left <= dist_right) {
			/*update target*/
			Target[kitty][0] = kitty_x-1;
			Target[kitty][1] = kitty_y;
		}
	}
 }
 /*kitty reached target*/
 if (kitty_x == Target[kitty][0] && kitty_y == Target[kitty][1]) {
 	Target[kitty][0] = -1;
	Target[kitty][1] = -1;
	return kittySmartSmell(GamePos, A, Target, kitty);	/*start smartSmell again*/
 }
 /*otherwise find the shortest path and keep updating it*/
 else {
 	path = PacoShortestPath(A, kitty_x, kitty_y, Target[kitty][0], Target[kitty][1]);
 	path = newPathNode(path->next->x, path->next->y);
 }
 return(path);
}

struct path_node *kittySoundWalk(int GamePos[numAgents][3], float A[GsizeSqr][GsizeSqr], int Target[numAgents][2], int kitty)
{
 /*
   Kitty sound walk: Expected behaviour:

   In space no one can hear you scream, unfortunately, we're not in space, so the
   mouse's little steps can be heard by hungry kitties.

   This function works by checking whether the mouse is closer than 'hearingRadius'
   away from a kitty. If so, the cat can hear the mouse and will use the shortest
   path to reach the mouse's location.

   ** As long as the mouse remains within hearing radius, the shortest path is
   ** updated at each turn (unlike kittySmartSmell() which computed a destination
   ** once and then had to wait for the cat to arrive there)

   If the mouse steps outside the hearing radius, the cat still has to complete
   the trip to the last known mouse location.

   As long as the mouse has not stepped within hearing radius, or if it stepped
   out and the cat reached the last known mouse location, the cat reverts to
   smell based mouse finding (you should use kittySmellWalk() for that - why
   can't you use kittySmartSmell()? )

   All distances are Manhattan distances.

   Depending on the value of hearingRadius (see GameAI.h), this could make the
   kitties pretty tough to beat, so don't make hearingRadius too large or the
   poor mouse doesn't stand a chance!

   Grid locations over which the mouse can be heard by one of the kitties
   will be shown in dark red on each frame (see renderFrame() if you want
   to change the way things look).
 */

 struct path_node *path=NULL;
 int mouse_x = GamePos[1][0], mouse_y = GamePos[1][1], kitty_x = GamePos[kitty][0], kitty_y = GamePos[kitty][1];
 int A_kitty = kitty_x + Gsize*kitty_y;		/*position of kitty in A*/
 int dist_mouse = abs(kitty_x-mouse_x) + abs(kitty_y-mouse_y);	/*manhattan distance till the mouse*/

 /*check to see if kitty has reached its target*/
 if(kitty_x == Target[kitty][0] && kitty_y == Target[kitty][1]) {
 	Target[kitty][0] = -1;		
 	Target[kitty][1] = -1;
 }
 /*if mouse stepped within hearing radius*/
 if (dist_mouse <= hearingRadius) {
 	path = PacoShortestPath(A, kitty_x, kitty_y, mouse_x, mouse_y);		/*update the shortest path each time*/
 	Target[kitty][0] = mouse_x;		/*update to new target*/
 	Target[kitty][1] = mouse_y;
 	return newPathNode(path->next->x, path->next->y);
 }
 /*mouse stepped outside hearing radius but the kitty has not yet reached its target*/
 else if (dist_mouse > hearingRadius && Target[kitty][0] != -1 && Target[kitty][1] != -1) {
 	path = PacoShortestPath(A, kitty_x, kitty_y, mouse_x, mouse_y);
	return path->next;
 }
 /*use smell walk to find the mouse*/
 else {
 	path = kittySmellWalk(GamePos, A, kitty);
 } 
 return(path);
}

struct path_node *EvilKittiesOfDoom(int GamePos[numAgents][3], float A[GsizeSqr][GsizeSqr], int kitty)
{
 /*
   Ever felt like the game you're playing was deliberately made impossible to beat?

   This function's only purpose is to show you what you *should not do* when designing
   a game AI.

   The only point to make here is this: A game agent should not acquire knowledge
   about the player or his character that can not be 'observed' directly by the
   agent. All other modes so far (1-4) use some form of sensing: vision, hearing,
   or smell to catch the mouse.

   Here we will cheat by providing the kitties with direct knowledge of exactly
   where the mouse is. Then the cats can use shortestPath() to get there.

   I am curious as to whether you can design the function mouseEscape() so that the
   mouse can still win even if the game is cheating by using this function to update
   cat positions!

   Behaviour: Very simple, at each turn compute the shortest path to the current
              mouse location, and move in that direction.
 */
 struct path_node *path=NULL;
 int mouse_x = GamePos[1][0], mouse_y = GamePos[1][1], kitty_x = GamePos[kitty][0], kitty_y = GamePos[kitty][1];
 /*just go to the mouse*/
 path = PacoShortestPath(A, kitty_x, kitty_y, mouse_x, mouse_y);
 return(path->next);
}

struct path_node *superKitty(int GamePos[numAgents][3], float A[GsizeSqr][GsizeSqr], int Target[numAgents][2], int kitty)
{
 /*
   ///////////////////
   // CRUNCHY: Implement this function to create the ultimate kitty mouse hunter!
   ///////////////////

   A super-kitty uses all possible means to capture the mouse: Sound, smell, and
   vision. Different modes of perception have different precedence:

   - Vision is first: If the cat can see the mouse it will move toward the mouse
                      regardless of any previously computed path.
   - Sound: As you saw, sound is pretty effective so if the mouse is not visible,
            kitties will try to use sound to locate the mouse and find a shortest
            path toward it.
   - Smell: If the mouse can't be seen or heard, smell is used to move in the
            general direction of the mouse.

   You probably want to use kittySmartSmell() to get around obstacles, but note
   that you will have a problem if kittySoundWalk() and kittySmartSmell() both
   want to update the Target[][] array with different destinations! If you're
   careful you should be able to pull it off by considering the rules of
   precedence mentioned above.

   I will be curious to see whether supperKitties are indeed unbeatable, or
   whether in fact your mouseEscape() function is smart enough to escape
   even the ultimate cat!
 */

 return(NULL);		// If you implement this function, remove this.
}

struct path_node *mouseWalk(int GamePos[numAgents][3],float A[GsizeSqr][GsizeSqr])
{
 /*
   Standard mouse walking function. The expected behavour is as follows:

   If the cheese has not been eaten. Compute the shortest path between the
   mouse and the cheese, return the path.

   If the cheese has been eaten. Compute the shortest path between the
   mouse and the gate and return the path.

   Requires the shortest path algorithm.
 */

 struct path_node *path=NULL;
 int cheese_mode = GamePos[2][2];
 int mouse_x =  GamePos[1][0], mouse_y = GamePos[1][1], cheese_x = GamePos[2][0], cheese_y = GamePos[2][1];
 int gate_x = GamePos[0][0], gate_y = GamePos[0][1];
 
 if (!cheese_mode) {		/*cheese not eaten*/
	path = PacoShortestPath(A, mouse_x, mouse_y, cheese_x, cheese_y);		/*travel to the cheese*/
	return path;
 }
 else {
	path = PacoShortestPath(A, mouse_x, mouse_y, gate_x, gate_y);		/*travel to the gate since cheese is eaten*/
	return path;
 }
	
 ////////////////////
 // CRUNCHY:
 //    The shortest path may go through a cat. That is not very smart, we would like
 //    to avoid any grid positions occupied by kitties. Make your code so that the
 //    shortest path can not possibly go through kitties. Note that you *must not*
 //    introduce any permanent changes in A[][] since cat positions are not
 //    a property of the graph. You must find some way to account for cat positions
 //    while computing shortest path without changing the original graph.
 //
 //    Note that a cat may be blocking the only path toward the exit (so no
 //    shortest path exists) - what will the mouse do then?
 ////////////////////

 //return(path);
}

struct path_node *mouseEscape(int GamePos[numAgents][3],float A[GsizeSqr][GsizeSqr])
{
 /*
    ////////////////////
    // CRUNCHY: Implement this function to create the smartest mouse possible
    ////////////////////

    So far, the mouse seems to mindlessly want to go for the cheese and then the gate.
    You may have altered mouseWalk() so that it doesn't compute a path through a
    cat, but that's about as smart as the mouse has got.

    Here, you should implement a mouse update function designed to elude even the
    smartest cat.

    Note that: The mouse can see the kitties (since the mouse would usually be
               user controlled, we assume the mouse sees where the kitties are).
               The mouse can also measure distance to the kitties.
               Of course, the mouse knows where the cheese and gate are.

    Design a maze traveling approach that gives the mouse a chance to escape even
    kitties using kittyAIcheat() or superKitty(). This will involve carefully
    managing the graph to account for cat position and proximity while optimizing
    the path to the cheese and the output.

    Don't let the mouse get caught! In particular, what will it do if the kitties
    are blocking the path toward the exit?

    There are many ways in which you can fill this function, feel free to come to
    my office if you want to discuss your approach.

    Good luck! the fate of mouse-kind may be in your hands!

    Note: Since this is a pretty difficult task, good solutions here will be
          worth a significant bonus.
 */

 struct path_node *path=NULL;

 return(path);
}

int main(int argc, char *argv[])
{
 /*
   This function sets everything up, and then goes into
   an update look for the agents. The loop ends when
   one of the following conditions is met:

   - The mouse got the cheese and went out the gate
   - A kitty ate the mouse

   For each update, a numbered image frame is generated
   and output to disk. The original format is .ppm but
   to save space, the code will attempt to convert the
   image to .jpg format using the Linux utility
   'convert' part of the imagemagick package (if you
   have your own Linux setup, make sure to install
   this package).

   At the end, the program will try to generate a
   short movie using 'mencoder' part of the 'mplayer'
   package. So if you want a movie make sure you
   also have installed this package.

   Needless to say if you're running this on Windows
   both the .jpg conversion and movie generation will
   fail, so you will have to do with still .ppm frames.
 */

 unsigned char R,G,B;		// Colour for maze plotting
 float A[GsizeSqr][GsizeSqr];	// Adjacency matrix to represent
				// the graph that describes the
				// maze grid
 int GamePos[numAgents][3];	// Array to hold game positions
				// for each agent, and update
				// mode
 int Target[numAgents][2];	// Array used to hold target grid coordinates
				// for agents. Used by functions that rely
                                // on shortest path but whose target may move
 struct image *sprites[numAgents];	// Pointers to the
					// images for each
					// agent
 struct image *maze;			// Pointer to the image that
					// holds the empty maze
 struct path_node *path, *path2;	// Pointers to hold a paths in the maze
 int frameno,seed;		
 int kitty_mode;		
 int mouse_mode;
 int user_choice,done;
 char line[1024];

 if (argc!=2)
 {
  fprintf(stderr,"Usage: GameAI random_seed\n");
  fprintf(stderr,"random_seed is the number used to initialize the random number generator.\n");
  fprintf(stderr,"We will use a specific value for this seed to check your code for mistakes.\n");
  exit(1);
 }
 seed=atoi(argv[1]);

 // Initialize random number generator
 srand48(seed);

 // Delete any frames left from previous runs
 sprintf(&line[0],"rm frame*.ppm frame*.jpg");
 system(line);

 // Load sprites representing game agents from disk
 loadSprites(sprites);

 // Allocate memory for the maze
 maze=(struct image *)calloc(1,sizeof(struct image));
 if (maze)
 {
  maze->sx=frameSize;
  maze->sy=frameSize;
  maze->rgbdata=(unsigned char *)calloc(maze->sx*maze->sy*3,sizeof(unsigned char));
  if (NULL==maze)
  {
   fprintf(stderr,"main(): Out of memory!\n");
   exit(1);
  }
 }
 else
 {
  fprintf(stderr,"Dude, this system is really out of memory\n");
  fprintf(stderr,"can't work under these conditions\n");
  exit(1);
 }

 // Zero out adjacency matrix and position array
 memset(A,0,GsizeSqr*GsizeSqr*sizeof(float));
 memset(GamePos,0,numAgents*3*sizeof(int));

 // Set targets to -1 initially (no target selected)
 for (int i=0; i<numAgents; i++) {Target[i][0]=-1;Target[i][1]=-1;}

 // Initialize the graph - See the initGraph() function for
 // a description of how the grid is encoded by A[][]
 initGraph(A,10,10,GamePos);

 // Create an MST for the graph so that we can build a maze.
 // Call Prim's method to generate an MST for the graph, this will reduce the
 // number of edges between nodes, which is equivalent to removing connections
 // between neighbours in the grid hence introducing walls and creating a
 // maze.

 PacoPrim(A);
 // Now, in an MST there is a single path from point A to point B
 // (as you have to show in the written portion of the assignment),
 // to make path finding more interesting let's add some
 // loops to the graph to create multiple paths from A to B.
 addLoops(A,numLoops);	// Add a specific number of loops by
			// re-connecting neighbours disconnected
			// by the MST generation step. Choose
			// randomly which edges to re-connect.

 // Finally, generate a maze from the graph.
 R=0;					// Make the initial maze blue
 G=0;
 B=255;
 graphToMaze(A,maze,R,G,B);

 // Output the empty maze to an image file so that we can check
 // your MST building code.
 imageOutput(maze,"maze.ppm");

 // Generate the first frame of the movie by placing the
 // agents in their starting position.
 frameno=0;
 renderFrame(GamePos,sprites,maze,NULL,frameno);

 // Let's check your shortest path algorithm by finding and
 // plotting the shortest path from (0,0) to (Gsize-1, Gsize-1)
 path=PacoShortestPath(A,0,0,Gsize-1,Gsize-1);
 if (path) {renderPath(maze,path, 50, 240, 240, 0); deletePath(path);}

 // Ask the user to select mode of operation for the kitties
 // and the mouse.
 done=0;
 while (!done)
 {
  done=1;
  fprintf(stderr,"Choose mode of operation for kitty agents:\n");
  fprintf(stderr,"1.- Eye walk\n");
  fprintf(stderr,"2.- Smell walk\n");
  fprintf(stderr,"3.- Smart-smell\n");
  fprintf(stderr,"4.- Sound walk\n");
  fprintf(stderr,"5.- Evil Kitties of Doom!\n");
  fprintf(stderr,"6.- Random (chooses for each kitty a mode in [1,4])\n");
  fprintf(stderr,"7.- (CRUNCHY) Super-kitty! (or, supper, kitty)\n");
  gets(&line[0]);
  sscanf(&line[0],"%d",&user_choice);
  if (user_choice<1||user_choice>7)
  {
   fprintf(stderr,"That is not a valid choice! try again\n");
   done=0;
  }
 }
 kitty_mode=user_choice;

 // Now ask the user for the mouse's mode of operation
 done=0;
 while (!done)
 {
  done=1;
  fprintf(stderr,"Choose mode of operation for the mouse:\n");
  fprintf(stderr,"1.- Shortest path\n");
  fprintf(stderr,"2.- (CRUNCHY) Mouse escape - no cat can catch this mouse (perhaps?!)\n");
  gets(&line[0]);
  sscanf(&line[0],"%d",&user_choice);
  if (user_choice<1||user_choice>2)
  {
   fprintf(stderr,"That is not a valid choice! try again\n");
   done=0;
  }
 }
 mouse_mode=user_choice;

 // Initialize agent modes as per the user's choice.
 // First, set the cats' mode of operation
 if (kitty_mode==6) for (int i=3; i<numAgents; i++) GamePos[i][2]=((int)(drand48()*3.99))+1;
 else for (int i=3; i<numAgents; i++) GamePos[i][2]=kitty_mode;
 // Now the mouse
 GamePos[1][2]=mouse_mode;
 // And the cheese - in this case the mode indicates whether the cheese has been
 // eaten or not. 0 means not eaten, anything else means eaten. This will affect
 // what the mouse is doing.
 GamePos[2][2]=0;

 // Done with initialization. Main game loop:
 // At each iteration, call the appropriate function to update the agents' 
 // positions, render the frame with the updated positions, then check 
 // for termination. The loop ends when the mouse has eaten the cheese
 // and reached the gate, or when it has been eaten by a cat.


 ////////////////////////////////////////////////////////////////
 //
 // NOTE: The code below is DISABLED for part a) of A4.
 //       Remove the exit(0) statement below when you are
 //       ready to work on part b). Keep in mind that
 //       when the main loop is enabled, it will write
 //       image frames to disk for every turn, and if your
 //       cat/mouse motion functions are not implemented
 //       this will go on and you will run out of disk space.
 //
 ///////////////////////////////////////////////////////////////
 //exit(0);	// Remove me! (when you are ready to work on part b) )

 done=0;
 while(done==0&&frameno<=maxFrames)
 {
  // NOTES:
  //  We re-compute the shortest path at each step. This may be wasteful if no
  //  kitties are near the mouse, or if we just don't care. However, here we
  //  allow for the possibility an agent may 'change its mind' based on the
  //  behaviour of other agents. 
  //  * be sure to delete any paths you create! *
  // 
  //  Also note that updates are *asynchronous*, the kitties are updated after
  //  the mouse, so in fact they may have an advantage in using the mouse's
  //  updated location.
  //

  frameno++;
  fprintf(stderr,"Frame number: %d, things are still moving along\n",frameno);

  // Update mouse position
  if (GamePos[1][2]==1)  // Shortest path mode
  {
   path2=mouseWalk(GamePos,A);
  }
  else
  {
   path2=mouseEscape(GamePos,A);
  }
  if (path2==NULL)
  {
   fprintf(stderr,"The mouse is trapped - nowhere to go?\n");
  }
  else
  {
   // Update mouse position. The shortest path starts at the current position, so we need path->next
   GamePos[1][0]=path2->next->x;
   GamePos[1][1]=path2->next->y;
  }

  // Since the update is asynchronous, we must check now that the mouse hasn't walked into a cat!! (that would be
  // bad for the mouse).
  for (int i=3; i<numAgents; i++)
   if (GamePos[1][0]==GamePos[i][0]&&GamePos[1][1]==GamePos[i][1]) done=2;

  // Update kitty positions
  if (done==0)
   for (int i=3;i<numAgents;i++)
   {
    path=NULL;
    switch (GamePos[i][2])
    {
     case 1:
      path=kittyEyeWalk(GamePos,A,i);
      break;
     case 2:
      path=kittySmellWalk(GamePos,A,i);
      break;
     case 3:
      path=kittySmartSmell(GamePos,A,Target,i);
      break;
     case 4:
      path=kittySoundWalk(GamePos,A,Target,i);
      break;
     case 5:
      path=EvilKittiesOfDoom(GamePos,A,i);
      break;
     case 7:
      path=superKitty(GamePos,A,Target,i);
      break;
     default:
      break;
    }
    if (path==NULL) 
    {
     fprintf(stderr,"Poor kitty #%d is stuck\n",i);
    }
    else
    {
     // Note: While for the mouse we look at path->next->[x,y] for kitties we look at
     // path->[x,y] directly since the functions that deal with cat position updates
     // return a single node.

     GamePos[i][0]=path->x;
     GamePos[i][1]=path->y;
     deletePath(path);
    }
   }

  // Render frame with updated positions.
  if (path2) renderFrame(GamePos,sprites,maze,path2->next,frameno);		// Show the mouse's planned path
  else renderFrame(GamePos,sprites,maze,NULL,frameno);				// Don't show the path
  if (path2) deletePath(path2);

  // Check for termination, cheese absorption, etc.
  if (GamePos[1][0]==GamePos[2][0]&&GamePos[1][1]==GamePos[2][1])
  {
   fprintf(stderr,"Cheese has been eaten! run for your life mouse!\n");
   GamePos[2][2]=1;
   R=0;			// Make the maze green to signal the eating of the cheese
   G=255;
   B=0;
   graphToMaze(A,maze,R,G,B);
   renderFrame(GamePos,sprites,maze,NULL,++frameno);
  }

  // Check to see if the mouse became kitty snack
  for (int i=3; i<numAgents; i++)
   if (GamePos[1][0]==GamePos[i][0]&&GamePos[1][1]==GamePos[i][1]) done=2;

  // Check to see if the mouse reached the gate
  if (GamePos[0][0]==GamePos[1][0]&&GamePos[0][1]==GamePos[1][1]) done=1;  

  // If you want to pause and check things between frames, uncomment the following line:
//  gets(&line[0]);
 } // End of main loop
 if (done==1) 
 {
  fprintf(stderr,"Mouse wins! (flawless victory!)\n");
  for (int i=1; i<9; i++)
  {
   R=255-R;
   G=255-G;
   B=255-B;
   graphToMaze(A,maze,R,G,B);
   renderFrame(GamePos,sprites,maze,NULL,frameno+i);		// Show the mouse's planned path   
  }
 }
 else{
  fprintf(stderr,"The mouse can now only eat cheese in the fields of dreams...\n");
  R=255;
  G=0;
  B=0;
  graphToMaze(A,maze,R,G,B);
  renderFrame(GamePos,sprites,maze,NULL,frameno);		// Show the mouse's planned path   
  for (int i=1; i<9; i++)
  {
   frameno++;
   R=255-R;
   G=255-G;
   B=255-B;
   graphToMaze(A,maze,R,G,B);
   renderFrame(GamePos,sprites,maze,NULL,frameno+i);		// Show the mouse's planned path   
  }
 }

 // Now, attempt to generate a movie from the frames of the video
 sprintf(&line[0],"mencoder \"mf://frame*.jpg\" -mf type=jpeg:fps=3 -ovc lavc -lavcopts vcodec=mjpeg -o MouseRun.mpg");
 system(line);

 // De-allocate memory assigned to images and sprites
 // Make sure you also release any memory allocated by
 // your code to path data structures.
 deleteImage(maze);
 for (int i=0; i<numAgents; i++) deleteImage(sprites[i]);

 exit(0);
}


