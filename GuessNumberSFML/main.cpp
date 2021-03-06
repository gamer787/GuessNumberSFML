#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <ctime>
#include <iostream>
#include <string>

#ifdef _DEBUG 
#include <iostream>
#endif

#undef AS_SHOWFRAMEINFO
#define W 800
#define H 600
#define FRAMERATE 27
#define WIN 4
#define COLD 3
#define WARM 2
#define HOT 1
#define BUT_SIZE 40
#define ROW_PADDING 5

#include "../../AnimsSFML/AnimsSFML/anims.cpp"

using namespace std;



////Variables\\\\
//GUI vars
sf::RenderWindow win;
/*--[[For the title]]--*/
sf::Font bubblegum;
sf::Text titleText;
sf::Clock titleNextFrame;
sf::Vector2<int> m( 50, 0 );
as::Animation<sf::Text*> t( &titleText, ( FRAMERATE * 0.5 ) );
/*--[[Square showing number]]--*/
sf::RectangleShape numPlace( sf::Vector2<float>( BUT_SIZE, BUT_SIZE ) );
sf::Texture spNumPlaceBase;
sf::Text number;
int XAxisAligner = ( ( W - 200 ) - ( BUT_SIZE * 10 + ROW_PADDING * 9 ) ) / 2;//This calculates the unused width from the [usable area], then divides it by to so it can be added to the objects, centering the game in the screen
int YAxisAligner = ( ( H - 90 ) - ( BUT_SIZE * 10 + ROW_PADDING * 9 ) ) / 2;
/*--[[Some debugging stuff]]--*/
sf::RectangleShape usableArea( sf::Vector2<float>( W - 200, H - 90 ) );
sf::CircleShape pointer( 3 );
//Mechanics vars
sf::Vector2i mouse(0,0);
int theChosenOne = -1;
int magicNumber = 1;
int * tried = new int(100);//This var stores the numbers that were tried and their result
/* 0: Nothings
   1: Cold
   2: Warm
   3: Hot
   4: That's it!
*/
short tries = 5;//Tries left

#include "functions.cpp"

int main() {
	sf::RenderWindow win( sf::VideoMode( W, H ), "Guessing Game!", sf::Style::Default );
	win.setFramerateLimit( FRAMERATE );
	win.setMouseCursorVisible( false );

	if( false == loadRes()  ) {//Resources loading
		#ifndef _DEBUG
		system("error.bat \"Resources loading failed\"");
		#endif // !_DEBUG
		return EXIT_FAILURE;
	}
	#ifdef _DEBUG
	std::cout << "Resource loading finished with no problems";
	#endif // _DEBUG


	////Object configuracion
	initObjects();

	init();//Game initializacion

	sf::Event event;
	while( win.isOpen() ) {
		while( win.pollEvent( event ) ) {
			switch( event.type ) {
				case sf::Event::Closed:
					win.close();
					break;
				case sf::Event::Resized:
					{
					sf::FloatRect visibleArea( 0, 0, event.size.width, event.size.height );
					win.setView( sf::View( visibleArea ) );}
					break;
				case sf::Event::KeyPressed:
					if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) ) {
						win.close();
						break;
					}
					if( sf::Keyboard::isKeyPressed( sf::Keyboard::BackSpace ) ) {
					}
					if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ) {
						#ifdef _DEBUG
						#endif // _DEBUG
					}
					if( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) ) init();
					break;
				case sf::Event::MouseButtonPressed:
					std::cout << "( " << mouse.x << "; " << mouse.y << " )\n";
					//std::cout << "( " << mose.getPosition().x << "; " << mose.getPosition().y << " )\n";
					if( mouse.y >= 90 && mouse.x >= 100 && mouse.x <= W - 100 ) {
						theChosenOne = getNumberClicked( mouse.x, mouse.y );
						if( theChosenOne == magicNumber ) {
							winGame();
						} else {
							hintPlayer();
						}
					}
					break;
				case sf::Event::MouseMoved:
					break;
				default:
					break;
			}
		}

		mouse = sf::Mouse::getPosition( win );

		win.clear();
		win.draw( usableArea );
		for( int i = 0; i < 100; i++ ) {
			int x, y;
			y = ( i - ( i % 10 ) ) / 10;
			x = i % 10;
			y = y * ( BUT_SIZE + ROW_PADDING ) + 90;
			x = x * ( BUT_SIZE + ROW_PADDING ) + 100;
			number.setString( to_string( i ) );
			number.setPosition( x + ( BUT_SIZE / 2 - number.getLocalBounds().width / 2 ) + XAxisAligner, y + ( BUT_SIZE / 2 - number.getLocalBounds().height / 2 ) - 5 + YAxisAligner );
			numPlace.setPosition( x + XAxisAligner, y + YAxisAligner );
			if( i == theChosenOne ) {
				//number.setFillColor(sf::Color::Red);
			}
			//number.setFillColor( tried[i] == COLD?sf::Color::Blue:( tried[i] == WARM?sf::Color::Yellow:sf::Color::Red ) );
			if( tried[i] == COLD )
				number.setFillColor( sf::Color::Blue );
			else if( tried[i] == WARM )

				number.setFillColor( sf::Color::Yellow );
			else if( tried[i] == HOT )
				number.setFillColor( sf::Color::Red );
			else  if( tried[i] == WIN )
				number.setFillColor( sf::Color::Green );
			else
				number.setFillColor( sf::Color( 197, 255, 255 ) );
			win.draw( numPlace );
			win.draw( number );
		}
		win.draw( titleText );
		#ifdef _DEBUG
		pointer.setPosition( win.mapPixelToCoords( mouse ) );
		win.draw( pointer );
		#endif // _DEBUG
		win.display();
		t.ProcessFrame( t.actFrame );
	}
}

