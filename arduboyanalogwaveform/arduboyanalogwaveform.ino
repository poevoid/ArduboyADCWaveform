#include <Arduboy2.h>

Arduboy2 arduboy;

int catprobe = 10; //pin to use as probe(+) in respect to the system's GND connection. Default is 10, this will show the waveform of the Red LED as INPUT. Value changes based on amount of light (in this case, red light) entered.
                   //The waveform of the red led wont be too interesting. mostly just a horizontal line that moves up and down depending on the amount of light entered. But go ahead and touch the LED, see what happens!
                   //Analog pins with 12+bit precision are best. Great for displaying audio waveforms from electret mics with a simple preamp like so:
                  /*
           _______________________________________________________________________________________________________
          |                                                                                                       |
          |                                                                                                       |
          |                .---------------------------------o------o------ +3-5v                                 |
          |                |                                        |                                             |
          |                |                                        |                                             |
          |                |                                       .-.                                            |
          |                |                                       | |                                            |
          |               .-.                                      10k                                            |
          |               | |                                      `-`                                            |
          |               10k                                       |                                             |
          |               `-`                          _______      |                                             |
          |                |                       |``|_______|`````|`````` OUT to analog (A1, A5, etc)           |
          |        (+)     |                       |     100k     |/                                              |
          |   /```\--------o-----------] [---------o--------------| 2N3904 (NPN)                                            |
          |  | mic |                 0.1-1.0uf                    |>                                              |    
          |   \.../........o                                        |                                             |
          |        (-)     |                                        |                                             |
          |                `----------------------------------------o---- GND                                     |    
          |                                                                                                       |    
          |_______________________________________________________________________________________________________|                  */


int sample;
int lastsample; 
int newy;
int yoffset = -412;
int ampVal =50;

struct Waveform {
  int x, y;
};

Waveform wave = {0,0};

void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(60);
  pinMode(catprobe, INPUT);
  power_adc_enable();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!arduboy.nextFrame()) return;
  arduboy.clear();
  displayWave();
  arduboy.display();
}


void displayWave(){
  for (wave.x = 0; wave.x < WIDTH; wave.x++) {
        
        sample = analogRead(catprobe);
        
        newy = (((sample *ampVal) / 64) - yoffset); //adjust this value until newy floats around 32  when ambient so the wave is visible onscreen  
        wave.y = newy;

        arduboy.drawLine( wave.x, lastsample, wave.x, wave.y);
        arduboy.setCursor(0, 32);
        lastsample = newy;
        arduboy.println(sample);
        arduboy.println(newy);
      }
}