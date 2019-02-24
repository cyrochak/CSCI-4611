/**
    CSci-4611 Assignment #1 Text Rain
**/


import processing.video.*;

// Global variables for handling video data and the input selection screen
String[] cameras;
Capture cam;
Movie mov;
PImage inputImage;
boolean inputMethodSelected = false;
float threshold = 128;
int count = 0;
ArrayList<Letter> rain = new ArrayList<Letter>();
String inputstring = "Hi My name is Cyro. I am a undergrate senior student studying Computer Science at the U of M, this is my first project on my Graphic class, which is called text rain,I hope you join my first graphical assignment in my lifetime.";
  

//make min max vel for pixel
// PImage  threshimage
// float threshold -0.5 
void setup() {
  size(1280, 720);  
  inputImage = createImage(width, height, RGB);
  textFont(loadFont("Calibri-20.vlw"));
  fill(0);
}

class Letter {
  int xpos,ypos,vel;
  int timescount;
  int randomLetter;
  
  Letter(){
   xpos = (int) random(0,width);
   ypos = 0;
   vel = (int) (0.5 + random(-1,1));
   timescount = 0;
   randomLetter = (int) (random(0,inputstring.length() - 1));
   text(inputstring.charAt(randomLetter),xpos,ypos);
   fill(#F51F07);
  }


void timesupdate() {
  this.ypos += this.vel;
  this.timescount += 1;
  text(inputstring.charAt(this.randomLetter),this.xpos,this.ypos);
}

}
void draw() {
  // When the program first starts, draw a menu of different options for which camera to use for input
  // The input method is selected by pressing a key 0-9 on the keyboard
  if (!inputMethodSelected) {
    cameras = Capture.list();
    int y=40;
    text("O: Offline mode, test with TextRainInput.mov movie file instead of live camera feed.", 20, y);
    y += 40; 
    for (int i = 0; i < min(9,cameras.length); i++) {
      text(i+1 + ": " + cameras[i], 20, y);
      y += 40;
    }
    return;
  }


  // This part of the draw loop gets called after the input selection screen, during normal execution of the program.

  
  // STEP 1.  Load an image, either from a movie file or from a live camera feed. Store the result in the inputImage variable
  
  if ((cam != null) && (cam.available())) {
    cam.read();
    inputImage.copy(cam, 0,0,cam.width,cam.height, 0,0,inputImage.width,inputImage.height);
  }
  else if ((mov != null) && (mov.available())) {
    mov.read();
    inputImage.copy(mov, 0,0,mov.width,mov.height, 0,0,inputImage.width,inputImage.height);
  }


  // Fill in your code to implement the rest of TextRain here..

  // Tip: This code draws the current input image to the screen
  set(0, 0, inputImage);

  if((cam != null))
  {
    pushMatrix();
    scale(-1,1);
    translate(-cam.width,0);
    image(cam,0,0);
    popMatrix();
  }
  
  filter(GRAY);
  if(count % 2 != 0)
  {
    filter(THRESHOLD);
  }
  
  Letter raindrop = new Letter();
  rain.add(raindrop);
  for (int i = 0; i < rain.size(); i++)
  {
    color detected = get(rain.get(i).xpos, rain.get(i).ypos);
    if (brightness(detected) < threshold)
    {
      rain.get(i).ypos -= 10;
      rain.get(i).timesupdate();
    } else {
      rain.get(i).timesupdate();
    }
    if (rain.get(i).ypos > height-10 || rain.get(i).timescount > 1600 )
    {
      rain.remove(i);
      i--;
      
    }
  }


}


void keyPressed() {
  
  if (!inputMethodSelected) {
    // If we haven't yet selected the input method, then check for 0 to 9 keypresses to select from the input menu
    if ((key >= '0') && (key <= '9')) { 
      int input = key - '0';
      if (input == 0) {
        println("Offline mode selected.");
        mov = new Movie(this, "TextRainInput.mov");
        mov.loop();
        inputMethodSelected = true;
      }
      else if ((input >= 1) && (input <= 9)) {
        println("Camera " + input + " selected.");           
        // The camera can be initialized directly using an element from the array returned by list():
        cam = new Capture(this, cameras[input-1]);
        cam.start();
        inputMethodSelected = true;
      }
    }
    return;
  }


  // This part of the keyPressed routine gets called after the input selection screen during normal execution of the program
  // Fill in your code to handle keypresses here..
  
  if (key == CODED) {
    if (keyCode == UP) {
      // up arrow key pressed
      threshold++;
    }
    else if (keyCode == DOWN) {
      // down arrow key pressed
      threshold--;
    }
  }
  else if (key == ' ') {
    // space bar pressed
    count++;
    filter(THRESHOLD);
  } 
  
}