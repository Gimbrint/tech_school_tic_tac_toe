// Library for controlling led's
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#include <math.h>

// The values for turns
#define cross 1
#define nought 2

// I forgot pin, also why can't i choose DIN or CKL?
int pinCS = 10; 
//Din connects to pin 11
//CLK connects to pin 13

bool changed = false;
bool wasChanged = false;
int currentImage = 0;
const unsigned char PROGMEM currentMap[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int numberOfHorizontalDisplays = 3;
int numberOfVerticalDisplays = 6;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

// Bitmaps for drawing!
const unsigned char PROGMEM smiley[] = {
  B00000000,
  B01000010,
  B00000000,
  B00011000,
  B10000001,
  B01000010,
  B00111100,
  B00000000,
  B01010101,
};
const unsigned char PROGMEM xMap[] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001,
};
const unsigned char PROGMEM oMap[] = {
  B00111100,
  B01000010,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B01000010,
  B00111100,
};

const unsigned char PROGMEM images[][9][8] = {
  {
    {
      B10101010,
      B01010101,
      B10101010,
      B01010101,
      B10101010,
      B01010101,
      B10101010,
      B01010101,
    },
  }
};
//  //  ###
//  //  Criss-Cross pattern
//  //  ###
//  {
//    {
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//    }, {
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//    }, {
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//    }, {
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//    }, {
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//    }, {
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//    }, {
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//    }, {
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//      B10101010,
//      B01010101,
//    }
//  },
//  //  ###
//  //  House
//  //  ###
//  {
//    {    // 1
//      B11110000,
//      B11110110,
//      B11100000,
//      B11000100,
//      B00010010,
//      B01001000,
//      B01000000,
//      B00000000,
//    }, {    // 2
//      B00000000,
//      B00000000,
//      B00000000,
//      B00000000,
//      B00000000,
//      B00000001,
//      B00000011,
//      B00000110,
//    }, {    // 3
//      B00000000,
//      B00000000,
//      B00000000,
//      B00000000,
//      B11000000,
//      B11100000,
//      B00110000,
//      B00011000,
//    }, {    // 4
//      B00000000,
//      B00000000,
//      B00000000,
//      B00000000,
//      B00000000,
//      B00000000,
//      B00000001,
//      B00000000,
//    }, {    // 5
//      B00001100,
//      B00011111,
//      B00001000,
//      B00101011,
//      B01111010,
//      B11011010,
//      B10001010,
//      B10001010,
//    }, {    // 6
//      B00001100,
//      B11111110,
//      B00000100,
//      B11000100,
//      B01000100,
//      B01000100,
//      B01000100,
//      B01000100,
//    }, {    // 7
//      B00000000,
//      B00000000,
//      B00000000,
//      B11111111,
//      B00000000,
//      B00100000,
//      B01000010,
//      B00000000,
//    }, {    // 8
//      B10001010,
//      B10001010,
//      B11111111,
//      B00000000,
//      B00001001,
//      B00100000,
//      B00000000,
//      B00000001,
//    }, {    // 9
//      B01000100,
//      B11111111,
//      B00000000,
//      B00001000,
//      B01000000,
//      B00000100,
//      B00000001,
//      B01000000,
//    }
//  }
////  //  ###
////  //  Snowman
////  //  ###
////  {
////    {    // 1
////      B00000000
////      B00000000
////      B00000000
////      B00000011
////      B00000100
////      B00000100
////      B00000011
////      B00000100
////    }, {    // 2
////      B00000000
////      B00111100
////      B11000011
////      B00000000
////      B00000000
////      B00000000
////      B11111111
////      B00000000
////    }, {    // 3
////      B00000000
////      B00000000
////      B00000000
////      B11000000
////      B00100000
////      B00100000
////      B11000000
////      B00100000
////    }, {    // 4
////      B00001000
////      B00001000
////      B00011000
////      B00101000
////      B01000100
////      B10000011
////      B00000100
////      B00001000
////    }, {    // 5
////      B00000000
////      B00000000
////      B00000000
////      B00000000
////      B00000000
////      B11111111
////      B00000000
////      B00000000
////    }, {    // 6
////      B00010000
////      B00010000
////      B00011000
////      B00010100
////      B00100010
////      B11000001
////      B00100000
////      B00010000
////    }, {    // 7
////      B00010000
////      B00010000
////      B00010000
////      B00010000
////      B00001000
////      B00000100
////      B00000011
////      B00000000
////    }, {    // 8
////      B00000000
////      B00000000
////      B00000000
////      B00000000
////      B00000000
////      B00000000
////      B00000000
////      B11111111
////    }, {    // 9
////      B00001000
////      B00001000
////      B00001000
////      B00001000
////      B00010000
////      B00100000
////      B11000000
////      B00000000
////    }
////  },
////  //  ###
////  //  Spiral
////  //  ###
////  {
////    {    // 1
////      B00000000
////      B00000111
////      B00011000
////      B00100000
////      B00100001
////      B01000010
////      B01000010
////      B01000100
////    }, {    // 2
////      B11111111
////      B00000000
////      B00011111
////      B01100000
////      B10000000
////      B00011110
////      B00100001
////      B00100000
////    }, {    // 3
////      B11000000
////      B00111000
////      B00000110
////      B11000001
////      B00100000
////      B00010000
////      B00001000
////      B10001000
////    }, {    // 4
////      B10000100
////      B10000100
////      B10000100
////      B10000100
////      B10000100
////      B10000100
////      B01000010
////      B01000010
////    }, {    // 5
////      B01000000
////      B01001100
////      B01010010
////      B01010010
////      B01001010
////      B01000010
////      B00100010
////      B00100100
////    }, {    // 6
////      B10001000
////      B10000100
////      B01000100
////      B01000100
////      B01000100
////      B01000100
////      B01000100
////      B10000100
////    }, {    // 7
////      B01000010
////      B00100001
////      B00100000
////      B00100000
////      B00010000
////      B00001110
////      B00000001
////      B00000000
////    }, {    // 8
////      B00011000
////      B00000001
////      B10000110
////      B01111000
////      B00000000
////      B00000011
////      B11111100
////      B00000000
////    }, {    // 9
////      B10000100
////      B00001000
////      B00001000
////      B00010000
////      B01100000
////      B10000000
////      B00000000
////      B00000000
////    }
//  }
//};

void setup() {
  Serial.begin(9600);
  matrix.setIntensity(10);
  
  matrix.setPosition(0, 0, 0); // 1st display: <0, 0>
  matrix.setPosition(1, 1, 0); // 2nd display: <1, 0>
  matrix.setPosition(2, 2, 0); // 3rd display: <2, 0>
  matrix.setPosition(3, 5, 0); // 4th display: <0, 1>
  matrix.setPosition(4, 4, 0); // 5th display: <1, 1>
  matrix.setPosition(5, 3, 0); // 6th display: <2, 1>
  matrix.setPosition(6, 6, 0); // 7th display: <0, 2>
  matrix.setPosition(7, 7, 0); // 8th display: <1, 2>
  matrix.setPosition(8, 8, 0); // 9th display: <2, 2>

  matrix.setRotation(0, 2);
  matrix.setRotation(1, 2);
  matrix.setRotation(2, 2);
  matrix.setRotation(6, 2);
  matrix.setRotation(7, 2);
  matrix.setRotation(8, 2);
  //matrix.setRotation(2, 1);
  //matrix.setRotation(3, 1);

  pinMode(8, INPUT);

  drawImage();
}

void loop() {
  if (!digitalRead(8)) {
    if (!wasChanged) {
      Serial.println("touched");
      wasChanged = true;
      currentImage = (currentImage + 1) % sizeof(images);
    }
  }
  else if (wasChanged) {
    delay(1000);
    wasChanged = !wasChanged;
  }
}

void drawImage() {
  for (int i = 0; i < 9; i++) {
    Serial.print("Got: ");
    matrix.drawBitmap(8*(i%3), 16-8*floor(i/3), images[0][i], 8, 8, HIGH);
  }
  matrix.write();
}



// ### THIS CODE IS USELESS, PLEASE DON'T THROW IT AWAY THOUGH! ###

//class Game {
//  public:
//    //int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//    //int turn = 1;
//    
//    Game() {
//      Serial.println("Hooray! We made a game exist!");
//      placePiece(0,0);
//      placePiece(1,0);
//      placePiece(2,0);
//      placePiece(0,1);
//      placePiece(1,1);
//      placePiece(2,1);
//      placePiece(0,2);
//      placePiece(1,2);
//      placePiece(2,2);
//      matrix.write();
//      Serial.println(checkWin());
//    }
//    void placePiece(int x, int y) {
//      int pos = x+3*y;
//      
//      if (turn == cross) {
//        drawXMap(x, y);
//        board[pos] = cross;
//      } else {
//        drawOMap(x, y);
//        board[pos] = nought;
//      }
//
//      //turn = 1 - turn;
//    }
//    bool checkWin() {
//      for (int i = 0; i <= 2; i++) {
//        if (
//          (board[3*i]==board[3*i+1] && board[3*i+1]==board[3*i+2]) // Check row
//          || (board[i]==board[i+3] && board[i+3]==board[i+6]) // Check column
//        ) return true;
//      }
//      // Diagonals
//      if (
//        (board[0]==board[4] && board[4]==board[9])
//        || (board[2]==board[4] && board[4]==board[7])
//      ) return true;
//      
//      return false;
//    }
//    void drawXMap(int x, int y) {
//      matrix.drawBitmap(8*x, 16-8*y, xMap, 8, 8, HIGH);
//    }
//    void drawOMap(int x, int y) {
//      matrix.drawBitmap(8*x, 8*y, oMap, 8, 8, HIGH);
//      matrix.write();
//    }
//};

//LedControl lc = LedControl(4,3,2, 1);
//
//bool shown = false;
//bool switched = false;
//int turn = cross;
//
//int xMap[64] = {
//  1, 0, 0, 0, 0, 0, 0, 1,
//  0, 1, 0, 0, 0, 0, 1, 0,
//  0, 0, 1, 0, 0, 1, 0, 0,
//  0, 0, 0, 1, 1, 0, 0, 0,
//  0, 0, 0, 1, 1, 0, 0, 0,
//  0, 0, 1, 0, 0, 1, 0, 0,
//  0, 1, 0, 0, 0, 0, 1, 0,
//  1, 0, 0, 0, 0, 0, 0, 1,
//};
//
//int oMap[64] = {
//  0, 0, 1, 1, 1, 1, 0, 0,
//  0, 1, 0, 0, 0, 0, 1, 0,
//  1, 0, 0, 0, 0, 0, 0, 1,
//  1, 0, 0, 0, 0, 0, 0, 1,
//  1, 0, 0, 0, 0, 0, 0, 1,
//  1, 0, 0, 0, 0, 0, 0, 1,
//  0, 1, 0, 0, 0, 0, 1, 0,
//  0, 0, 1, 1, 1, 1, 0, 0,
//};
//
//void setup() {
//  // put your setup code here, to run once:
//  pinMode(inputPin, INPUT);
//  Serial.begin(9600);
//
//  lc.shutdown(0,false);
//
//  /* Set the brightness to a medium values */
//  lc.setIntensity(0,8);
//  /* and clear the display */
//  lc.clearDisplay(0);
//  delay(100);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  if (digitalRead(inputPin) == LOW) {
//    if (!shown) {
//      for (int i = 0; i < 64; i++) {
//        if (turn == 1) {
//          if (oMap[i] == 1) {
//            lc.setLed(0, i%8, i>>3, 1);
//          }
//        }
//        else if (xMap[i] == 1) {
//          lc.setLed(0, i%8, i>>3, 1);
//        }
//      }
//      
//      shown = true;
//    }
//  }
//  else if (shown) {
//    turn = 1 - turn;
//    shown = false;
//    lc.clearAll();
//  }
//}
