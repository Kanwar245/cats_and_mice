cats_and_mice
=============

<div id="page_1">

<div class="dclr"></div>
<p class="p1 ft1">Design and Analysis of Data Structures: Project 4</p>
<p class="p2 ft0">Cats and Mice and Game A.I.s</p>
<p class="p3 ft0">May the best <nobr>graph-based</nobr> algorithm win!</p>
</div>
<div id="page_2">


<div class="dclr"></div>
<div id="id_1">
<p class="p5 ft2">The kitties are on the loose. What is a poor, <nobr>hard-working</nobr> mouse to do?</p>
<p class="p6 ft3">This project is all about having fun with graphs. As we have already discussed in class, graphs are used in a very wide range of applications including artificial intelligence.</p>
<p class="p7 ft4">For this project, you will take the role of both the mouse trying to find some lunch and get away before becoming lunch, and the kitties who are always hungry and looking for unsuspecting customers. You will be using a variety of graph based algorithms,</p>
<p class="p8 ft6">and you will be responsible for planning the movement of each <span class="ft5">agent </span>in the maze.</p>
<p class="p9 ft5">Learning Goals for this project:</p>
<p class="p10 ft5">After completing this project, you should be able to:</p>
<p class="p11 ft6"><span class="ft6">*</span><span class="ft7">Explain the structure of heaps and how to use them to implement priority queues</span></p>
<p class="p11 ft6"><span class="ft6">*</span><span class="ft7">Store and manipulate graphs using adjacency matrices</span></p>
<p class="p12 ft6"><span class="ft6">*</span><span class="ft7">Implement Prim's MST and Dijkstra's shortest path algorithms</span></p>
<p class="p13 ft6"><span class="ft6">*</span><span class="ft7">Use graph and graph algorithms to implement a simple game of cat(s) and mouse</span></p>
<p class="p14 ft8">The above goals directly support your learning of material presented in the final weeks of the course. Additionally, this project is an opportunity to learn about:</p>
<p class="p12 ft6"><span class="ft6">*</span><span class="ft7">Path finding and path planning, fundamental topics in </span><span class="ft5">A.I.</span></p>
<p class="p12 ft6"><span class="ft6">*</span><span class="ft7">Interacting with the </span><span class="ft5">O/S </span>from your C program</p>
<p class="p12 ft6"><span class="ft6">*</span><span class="ft7">Creating random mazes using trees</span></p>
<p class="p15 ft3"><span class="ft6">*</span><span class="ft9">Representing and manipulating the </span><span class="ft10">state </span>of different agents in the game, <nobr>state-based</nobr> planning.</p>
<p class="p16 ft4">Same as in project 2, there are places marked <span class="ft8">“// CRUNCHY:” </span>where you can have additional fun expanding and modifying the code. Crunchy bits are also</p>
<p class="p17 ft6">worth extra credit.</p>
<p class="p18 ft10">There are 2 parts to this project, with two different deadlines. Be sure to complete the work required for part A on time. No extensions can be given for either part A or B since we are constrained by the end of term.</p>
</div>
<div id="id_2">
<div id="id_2_1">
<p class="p19 ft11">Be sure to review the material on graphs in the online notes.</p>
</div>
<div id="id_2_2">
<p class="p19 ft5">Have FUN!</p>
</div>
</div>
</div>
<div id="page_3">
<div id="dimg1">
<img src="A4_2012_images/A4_20123x1.jpg" id="img1">
</div>


<div class="dclr"></div>
<div id="id_1">
<p class="p20 ft2">Basic setup:</p>
<p class="p21 ft13">The action takes place within a maze. The maze consists of a square grid with <span class="ft12">Gsize </span>positions along both the <span class="ft12">x </span>and <span class="ft12">y </span>directions. Each location in the maze is represented as a node in a graph <span class="ft12">G(V,E)</span>, and the edges between <span class="ft12">neighboring </span>nodes represent the connectivity of the maze. Note that because the graph represents a 2D maze, each node can be connected to <span class="ft12">at most 4 other nodes</span>: its neighbours in the up, down, left, and right directions. Each grid location is given an <span class="ft12">index </span>starting at zero for the <nobr>top-left</nobr> corner and going up to <nobr>(<span class="ft12">Gsize*Gsize)-1</span></nobr><span class="ft12"> </span>for the <nobr>bottom-right</nobr> corner</p>
<p class="p20 ft6">as shown below:</p>
<table class="t0" cellpadding="0" cellspacing="0">
<tbody><tr>
	<td class="tr0 td0"><p class="p22 ft14">&nbsp;</p></td>
	<td colspan="2" rowspan="2" class="tr1 td1"><p class="p23 ft16">0 1 2 <span class="ft15">...</span></p></td>
	<td class="tr0 td2"><p class="p24 ft16"><nobr>Gsize-1</nobr></p></td>
</tr>
<tr>
	<td class="tr2 td0"><p class="p22 ft14">&nbsp;</p></td>
	<td rowspan="2" class="tr3 td2"><p class="p25 ft16"><nobr>(2*Gsize)-1</nobr></p></td>
</tr>
<tr>
	<td rowspan="2" class="tr4 td0"><p class="p22 ft16">Gsize</p></td>
	<td class="tr5 td3"><p class="p22 ft17">&nbsp;</p></td>
	<td class="tr6 td4"><p class="p22 ft18">&nbsp;</p></td>
</tr>
<tr>
	<td class="tr7 td5"><p class="p22 ft19">&nbsp;</p></td>
	<td class="tr7 td4"><p class="p22 ft19">&nbsp;</p></td>
	<td class="tr7 td2"><p class="p22 ft19">&nbsp;</p></td>
</tr>
</tbody></table>
<p class="p26 ft16"><nobr>(Gsize*Gsize)-1</nobr></p>
</div>
<div id="id_2">
<div id="id_2_1">
<table class="t1" cellpadding="0" cellspacing="0">
<tbody><tr>
	<td class="tr8 td6"><p class="p27 ft6">0</p></td>
	<td class="tr8 td7"><p class="p27 ft6">1</p></td>
	<td class="tr8 td8"><p class="p27 ft6">2</p></td>
	<td class="tr8 td9"><p class="p27 ft6">3</p></td>
</tr>
</tbody></table>
<table class="t2" cellpadding="0" cellspacing="0">
<tbody><tr>
	<td class="tr9 td5"><p class="p27 ft6">20</p></td>
	<td class="tr9 td10"><p class="p27 ft6">21</p></td>
	<td class="tr9 td8"><p class="p27 ft6">22</p></td>
	<td class="tr9 td8"><p class="p27 ft6">23</p></td>
</tr>
</tbody></table>
<table class="t2" cellpadding="0" cellspacing="0">
<tbody><tr>
	<td class="tr8 td5"><p class="p27 ft6">40</p></td>
	<td class="tr8 td10"><p class="p27 ft6">41</p></td>
	<td class="tr8 td8"><p class="p27 ft6">42</p></td>
	<td class="tr8 td8"><p class="p27 ft6">43</p></td>
</tr>
</tbody></table>
</div>
<div id="id_2_2">
<p class="p28 ft13">The enlarged area shows how grid positions map to a corresponding node in the graph (I'm assuming here that <span class="ft12">Gsize=20</span>). Connections between nodes encode maze connectivity. In</p>
<p class="p29 ft3">particular, absence of an edge between neighbouring nodes indicates the presence of a wall in the maze.</p>
<p class="p30 ft3">The weights of all edges in the maze graph are equal to 1.0</p>
</div>
</div>
</div>
<div id="page_4">
<div id="dimg1">
<img src="A4_2012_images/A4_20124x1.jpg" id="img1">
</div>


<div class="dclr"></div>
<div id="id_1">
<p class="p20 ft2">First Task:</p>
<p class="p31 ft4"><span class="ft8">Build the maze! </span>The first thing we need to do is to set up the maze in which the agents will interact. Maze creation is an interesting topic by itself, and you may want to check the wiki page on it before proceeding.</p>
<p class="p32 ft3">The function <span class="ft10">initGraph() </span>in the starter code sets up a graph structure for you. The initial graph is <span class="ft10">connected</span>, and every node has a link to each of its neighbours (note that nodes along the border of the grid have fewer than 4 neighbours).</p>
<p class="p33 ft4">Initially, the weight of each edge is random. Based on the setup described in the previous page, the initial graph corresponds to a maze with no walls. <span class="ft8">Compile and run the starter code and verify that you indeed obtain an empty maze, note the program takes one command line parameter: the initial random seed</span>. Your task is to select a set of edges to remove from this graph thereby introducing walls. However, doing this randomly will not result in a nice maze, so we have to do something smart.</p>
<p class="p34 ft3">Note that we can think of maze generation as the problem of selecting which subset of the edges in the initial graph to keep, and which to discard. We will impose the following conditions on the maze:</p>
<p class="p35 ft4"><span class="ft6">-</span><span class="ft20">It should be connected: There should be at least one path between any pair of grid locations.</span></p>
<p class="p36 ft6"><span class="ft6">-</span><span class="ft7">It should have at least a few loops (think about why that may be a good thing).</span></p>
<p class="p37 ft3">There are many ways to build a maze from a graph. Here, we will use <span class="ft10">Prim's algorithm </span>to generate an <span class="ft10">MST</span>, since the initial weights between nodes are random, this is equivalent to creating a new, connected graph with random paths between edge pairs.</p>
<p class="p38 ft4">Your task will be to implement <span class="ft8">Prim's algorithm </span>(see <span class="ft8">graph_algorithms.c</span>). Once you have completed Prim's algorithm, test to make sure you obtain a maze, and that the resulting maze is fully connected (if there are isolated grid locations or disconnected regions in the maze, you have a bug in Prim's method). The starter code will generate an image called 'maze.ppm' or 'maze.jpg' (more on that in a sec.) to ease your testing.</p>
<p class="p39 ft4">The starter code already has a function to introduce loops after running Prim's method, so you don't need to worry about that. You can select how many loops to introduce</p>
<p class="p17 ft6">by changing the appropriate value in <span class="ft5">GameAI.h</span>.</p>
</div>
<div id="id_2">
<p class="p40 ft11"><img src="A4_2012_images/A4_20124xi2.jpg" id="inl_img1"> For efficiency, you should use <img src="A4_2012_images/A4_20124xi3.jpg" id="inl_img2"> heaps and priority queues<img src="A4_2012_images/A4_20124xi4.jpg" id="inl_img3"></p>
</div>
</div>
<div id="page_5">
<div id="dimg1">
<img src="A4_2012_images/A4_20125x1.jpg" id="img1">
</div>


<div class="dclr"></div>
<div id="id_1">
<p class="p20 ft2">Notes on Prim's algorithm</p>
<p class="p41 ft22">The MST function will replace the original graph (the one with the random edge weights) with the resulting MST. <span class="ft21">Note that the weight of all edges in the MST must be 1.0</span>. We will <span class="ft21">not </span>keep the random edge weights since they would be meaningless in terms of computing the length of the path between two maze locations.</p>
<p class="p42 ft2">Second Task:</p>
<p class="p43 ft3">Implement <span class="ft10">Dijkstra's shortest path algorithm</span>. Your implementation should be able to compute the shortest path between any pair of nodes in the graph. The algorithm is short and straightforward, but you <span class="ft10">must know what you're doing </span>on the graph.</p>
<p class="p44 ft4">Test your shortest path algorithm thoroughly since it will be used extensively. Once you have completed the shortest path function, the starter code will generate an image called <nobr>'path_0-0.ppm'</nobr> (or <nobr>'path_0-0.jpg'),</nobr> showing the shortest path from the <nobr>top-left</nobr> corner of the grid to the <nobr>bottom-right</nobr> corner. Make sure the path is correct, and test with different pairs of grid points until you're sure it works always.</p>
<p class="p45 ft23">For part A, you need only complete Prim's algorithm and Dijkstra's shortest path method.</p>
<p class="p49 ft5">Part A grading:</p>
<p class="p50 ft8">(25 marks) Fast Prim's algorithm using heaps and priority queues or</p>
<p class="p17 ft5">(10 marks) Slow Prim's algorithm using the adjacency matrix A directly</p>
<p class="p51 ft5">(20 marks) Dijkstra's shortest path method</p>
<p class="p52 ft23">(5 marks) Completed the required information for part A in the file REPORT.TXT (included with the starter code)</p>
</div>
</div>
<div id="page_6">
<div id="dimg1">
<img src="A4_2012_images/A4_20126x1.jpg" id="img1">
</div>

<div id="tx1"><span class="ft25">There is a good reason why I can update my projected path at every turn. See the crunchy stuff...</span></div>

<div class="dclr"></div>
<p class="p20 ft2">Task 3: Game A.I.</p>
<p class="p56 ft3">Now that you have all the components of your graph working, it's time to implement the algorithms that will update the positions of the mouse and kitties in the maze. This is where you get to get to do path planning, one common task in Artificial Intelligence.</p>
<p class="p57 ft5">Mouse A.I. – Simple and fast</p>
<p class="p58 ft4">In a typical game, the mouse would be controlled by a user. Here, we will update the mouse position automatically. However, since the mouse represents the player, we will assume the mouse can 'see' the entire maze, including the positions of the cheese and gate as well as the kitties.</p>
<p class="p51 ft6">The strategy for the mouse updates is simple:</p>
<p class="p59 ft6"><span class="ft6">*</span><span class="ft7">The mouse will use the shortest path algorithm to get to wherever it's going.</span></p>
<p class="p60 ft6"><span class="ft6">*</span><span class="ft7">The mouse must eat the cheese, and then escape before being eaten.</span></p>
<p class="p61 ft5">Simple mouse A.I.</p>
<p class="p62 ft3">Implement the function <span class="ft10">mouseWalk()</span>. This function computes and returns the shortest path between the mouse and its target (the cheese if it has not been eaten, or the gate if the mouse had his lunch).</p>
<p class="p63 ft3">If you completed this successfully, you should see the mouse moving toward the target in successive frames output by the program.</p>
<p class="p64 ft3">That's it for the mouse, however, see the <span class="ft10">mouseWalk() </span>function for a crunchy problem that you may want to solve to give the mouse a better chance of not running directly Into a cat!</p>
<p class="p57 ft5">About Shortest Path and A.I.</p>
<p class="p65 ft4">The shortest path algorithm seems like is a reasonable choice for updating the</p>
<p class="p66 ft4">mouse's behaviour... or is it? One problem with our mouse update strategy is that</p>
<p class="p67 ft13">it does not consider at all the position and behaviour of the kitties. What would you do to incorporate information about the cats and their behaviour</p>
<p class="p8 ft6">into the mouse update function?</p>
<p class="p68 ft3">If you want to think about it, look at the crunchy bits in the starter code.</p>
</div>
<div id="page_7">
<div id="dimg1">
<img src="A4_2012_images/A4_20127x1.jpg" id="img1">
</div>


<div class="dclr"></div>
<div id="id_1">
<p class="p20 ft5">Kitty AI – Cats are smart, and they own the house...</p>
<p class="p70 ft6">Kitty AI is more interesting, the kitties are the agents that would be controlled by</p>
<p class="p71 ft3">the program in a typical game. The goal of the kitties is, of course, to eat the mouse. You will explore different ways to control cat behaviour. At the beginning of the program the user can select which <span class="ft10">mode </span>of cat behaviour will be used.</p>
<p class="p57 ft6">The modes of cat behaviour you have to implement are:</p>
<p class="p72 ft3"><span class="ft10">Visual cats: </span>They wander randomly through the maze, however, if they can 'see' the mouse, they will give chase. A kitty can see a mouse if both are aligned horizontally or vertically and there are no walls in between.</p>
<p class="p73 ft4"><span class="ft8">Scent tracking cats: </span>They do not know exactly where the mouse is, but can tell whether a grid location next them is closer or farther from the mouse and move in the direction that puts them closer to the Mouse. Unfortunately, they tend to get stuck...</p>
<p class="p74 ft4"><span class="ft8">Smart scent tracking kitties: </span>They use smell as described above, but if they get stuck due to a wall blocking their path, they can use the shortest path method to <span class="ft8">get to the other side of the wall</span>. Once on the other side, they continue using smell.</p>
<p class="p75 ft3"><span class="ft10">Sound chasing kitties: </span>These kitties use their ears. If the mouse steps within a specified distance from the cat, they will hear it and use the shortest path algorithm to get to where the mouse is making noise.</p>
<p class="p76 ft4"><span class="ft8">Evil Cats of Doom: </span>These exist to show you what happens when the game designer allows the AI to gain knowledge it shouldn't have. In this case, you will provide the cats with the actual location of the mouse, and the kitties will use the shortest path method to get there.</p>
<p class="p77 ft3">Read the corresponding function header in the starter code for a description of the behaviour of each function.</p>
</div>
<div id="id_2">
<div id="id_2_1">
<p class="p19 ft5">Your task is to implement all of the</p>
<p class="p78 ft8">cat behaviours described above. <span class="ft4">You will need to enforce graph connectivity (even these kitties can not walk through walls), and you will explore how the choice of algorithm for cat behaviour influences the mouse's chance of success.</span></p>
</div>
<div id="id_2_2">
<p class="p79 ft25"><img src="A4_2012_images/A4_20127xi2.jpg" id="inl_img1"> Test kitty A.I. thoroughly, and remember there are <img src="A4_2012_images/A4_20127xi3.jpg" id="inl_img2">harder and easier mazes!</p>
</div>
</div>
</div>
<div id="page_8">
<div id="dimg1">
<img src="A4_2012_images/A4_20128x1.jpg" id="img1">
</div>


<div class="dclr"></div>
<div id="id_1">
<p class="p81 ft5">Building a Super Cat **CRUNCHY!**</p>
<p class="p82 ft4">The kitty update functions you have to implement offer a good glimpse into strategies you could use to find and chase a game character. However, you may be inclined to investigate how 'smart' you can make the kitties without actually cheating (i.e. without providing them with the location of the mouse).</p>
<p class="p83 ft4">One thing you can try, is to arm each kitty with all possible modes of mouse tracking: <span class="ft8">vision, smell, and sound</span>. You would have to deal with the precedence of each sense in the overall cat behaviour, and determine how they interact to bring the kitties toward the mouse and hopefully get them some lunch.</p>
<p class="p84 ft3">If you're curious to try, the function <span class="ft10">superKitty() </span>in the starter code is the place for you. see how smart you can make the cats and feel free to add your own ideas. Remember That you <span class="ft10">can not provide the kitties with any knowledge of the mouse, cheese location, or gate location </span>that they can not acquire directly by exploring the maze.</p>
<p class="p85 ft5">Building a smarter Mouse **CRUNCHY!**</p>
<p class="p86 ft3">This is the most interesting (and most fun) part of this project. Here you can try more advanced A.I. techniques to try and make your mouse impossible to catch. The only constraints for you are these:</p>
<p class="p87 ft6"><span class="ft6">*</span><span class="ft7">The mouse can not escape until it has eaten the cheese</span></p>
<p class="p88 ft6"><span class="ft6">*</span><span class="ft7">The mouse can not teleport or move through walls</span></p>
<p class="p89 ft3"><span class="ft6">*</span><span class="ft9">The mouse can not see into the future (i.e. it should not see where the cats will move to in the next round)</span></p>
<p class="p90 ft4">You are free to use information about <span class="ft8">current </span>cat location and even their mode of operation. You may want to look at search algorithms such as <span class="ft8">A* search</span>, you could use the shortest path algorithm together with separately enforced constraints, you could use breadth first or depth first search, or you can even get ambitious and do a bit of simulation to try to <span class="ft8">predict </span>where the cats will go.</p>
<p class="p91 ft3">See the function <span class="ft10">mouseEscape() </span>and feel free to drop by my office if you want to discuss your strategy or simply talk a bit about A.I.</p>
<p class="p92 ft3">This should encourage you to think about what exactly makes an algorithm 'smart', and whether you can make your mouse smart enough to escape any cats!</p>
<table class="t3" cellpadding="0" cellspacing="0">
<tbody><tr>
	<td class="tr0 td11"></td>
	<td class="tr0 td12"><p class="p22 ft11">I sense a roasted</p></td>
	<td rowspan="2" class="tr10 td13"><p class="p22 ft25">This furball can't</p></td>
</tr>
<tr>
	<td class="tr7 td11"></td>
	<td rowspan="2" class="tr11 td12"><p class="p22 ft11">mouse for dinner!</p></td>
</tr>
<tr>
	<td class="tr12 td11"></td>
	<td rowspan="2" class="tr11 td13"><p class="p22 ft11">catch me!</p></td>
</tr>
<tr>
	<td class="tr7 td11"></td>
	<td class="tr7 td12"><p class="p22 ft19">&nbsp;</p></td>
</tr>
</tbody></table>
</div>
<div id="id_2">
<p class="p19 ft26">S.K.</p>
</div>
</div>
<div id="page_9">
<div id="dimg1">
<img src="A4_2012_images/A4_20129x1.jpg" id="img1">
</div>


<div class="dclr"></div>
<p class="p94 ft5">Part B Grading:</p>
<p class="p95 ft8">(5 marks) : Completed mouseWalk() function for updating mouse position (10 marks): Completed kittyEyeWalk() function for visual cats</p>
<p class="p8 ft5">(5 marks): Complete kittySmellWalk() function for scent tracking cats</p>
<p class="p96 ft8">(10 marks): Completed kittySmartSmell() function for smart scent tracking cats (10 marks): Completed kittySoundWalk() function for sound following kitties (5 marks): Completed EvilKittiesOfDoom() function</p>
<p class="p8 ft5">(5 marks): Completed all questions and information in REPORT.TXT</p>
</div>


