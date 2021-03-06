////Functions\\\\
//Functionality
void centerText( sf::Text *t, sf::Vector2<int> cd );//Duh...
int getNumberClicked( int x, int y );
void winGame();
int hintPlayer();
//Startup
bool loadRes();//Find and load resources
void init();//Reset game data to play again
void initObjects();

//Functionality
void centerText( sf::Text *t, sf::Vector2<int> cd ) {
	( *t ).setPosition( ( cd.x / 2 - ( *t ).getGlobalBounds().width / 2 ) + ( *t ).getOrigin().x, cd.y + ( *t ).getOrigin().y );//Centrar texto
}

int getNumberClicked( int x, int y ) {
	sf::Vector2<int> boardClick( ( x - ( 100 + XAxisAligner ) ), ( y - ( YAxisAligner + 90 ) ) );//Store the coords relative to the game, not the top-left window corner
	sf::Vector2<int> gridClick( -1, -1 );//Row and column clicked (x+y*10=number)
	int number = -1;//Clicked number, if [number]<0||[number]>99 then nothing was clicked
	for( int col = 0; col <= 10; col++ ) {
		if( boardClick.x > col*( BUT_SIZE + ROW_PADDING ) && boardClick.x < ( col*( BUT_SIZE + ROW_PADDING ) ) + BUT_SIZE ) {
			std::cout << "X: " << col << std::endl;
			gridClick.x = col;
		}
		if( boardClick.y > col*( BUT_SIZE + ROW_PADDING ) && boardClick.y < ( col*( BUT_SIZE + ROW_PADDING ) ) + BUT_SIZE ) {
			std::cout << "Y: " << col << std::endl;
			gridClick.y = col;
		}
	}
	if( gridClick.x != -1 && gridClick.y != -1 )
		number = gridClick.y * 10 + gridClick.x;
	else
		number = -1;
	return number;
}

void winGame() {
	std::cout << "Win";
	tried[theChosenOne] = WIN;

}

int hintPlayer() {
	unsigned int nearRange = COLD;//If it isn't warm or hot, then use the default value: Cold
	std::cout << "Generating hint\n";

	short hotMinRange = theChosenOne - 4, hotMaxRange = theChosenOne + 4;
	short warmMinRange = theChosenOne - 7, warmMaxRange = theChosenOne + 7;

	//Check if the ranging numbers are offset
	{
		if( hotMinRange < 0 )
			hotMinRange += 100;
		if( hotMaxRange >= 100 )
			hotMaxRange -= 100;
		if( warmMinRange < 0 )
			warmMinRange += 100;
		if( warmMaxRange >= 100 )
			warmMaxRange -= 100;
	}

	if( warmMinRange < magicNumber && warmMaxRange > magicNumber )//Warm
		nearRange = WARM;
	if( hotMinRange < magicNumber && hotMaxRange > magicNumber )//Hot
		nearRange = HOT;
	switch( nearRange ) {
		case 3:
			std::cout << "Cold";
			break;
		case 2:
			std::cout << "Warm";
			break;
		case 1:
			std::cout << "Hot";
			break;
		default:
			break;
	}
	tried[theChosenOne] = nearRange;
	return nearRange;
}

//Startup
bool loadRes() {
	string res = "Res\\";
	return bubblegum.loadFromFile( res + "Bubblegum.ttf" ) &&
		spNumPlaceBase.loadFromFile( res + "PlaceholderForNums.png" );

}

void init() {//This function should run every time the game is initialized
	for( int i = 0; i < 100; i++ ) tried[i] = 0;
	srand( time( NULL ) );
	magicNumber = ( (float)rand() / RAND_MAX * 100 );
	#ifdef _DEBUG
	std::cout << "Magic number: " << magicNumber;
	#endif
	//tried = { 3 };
}

void initObjects() {//This function should only run ONCE
	//Title
	titleText.setFont( bubblegum );
	titleText.setOutlineColor( sf::Color( 242, 156, 216 ) );
	titleText.setOutlineThickness( 2 );
	titleText.setString( "Guessing Game!" );
	titleText.setOrigin( titleText.getGlobalBounds().width / 2, titleText.getGlobalBounds().height / 2 );
	centerText( &titleText, sf::Vector2<int>( W, 50 ) );
	titleText.setRotation( -15 / 4 );
	t.Rotate( 15 / 2, false, 0, t.frames / 2 );
	t.Rotate( -15 / 2, false, t.frames / 2, t.frames );
	//Number placeholder
	numPlace.setTexture( &spNumPlaceBase );
	numPlace.setPosition( W / 2, H / 2 );
	number.setFont( bubblegum );
	number.setFillColor( sf::Color( 197, 255, 255 ) );
	number.setOutlineColor( sf::Color::Black );
	number.setOutlineThickness( 1 );
	number.setString( "0" );
	//Debugging stuff
	usableArea.setPosition( sf::Vector2<float>( ( float )100.0, ( float )90.0 ) );
	usableArea.setFillColor( sf::Color( 25, 25, 25 ) );
	pointer.setFillColor( sf::Color::Red );
}
