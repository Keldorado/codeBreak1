//THIS CODE WAS DEVELOPED BY ANDREAS MULLER


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    
    void resolutionChanged( int& _res );
    
    gui.setup( "Main", "Main.xml" );
    
    gui.add( resolution.set( "Resolution", 512, 2, 1024 ) ); //Adds a slider to affect the resolution
    gui.add( noiseFrequency.set( "Noise Frequency", 80.0f, 0.00001f, 4096.0f ) ); //Adds a slider to affect the noise frequency
    gui.add( animate.set( "Animate", false ) ); //Adds a slider a slider to afect the animation
    
    resolution.addListener(this, &ofApp::resolutionChanged); //listens to see if resolution has changed
    
    //Adds a slider to affect the threashold levels
    gui.add( doThreshold.set( "Threshold", false ) );
    gui.add( thresholdLow.set( "Treshold Low", 0, 0, 255 ) );
    gui.add( thresholdHigh.set( "Treshold High", 127, 0, 255 ) );
    
    //Adds a slider to invert the threashold starting in the "off" position
    gui.add( invert.set( "Invert Threshold", false ) );
    
    //Where in the noise pattern you are reading the noise
    noiseStartX = 150;
    noiseStartY = 150;
    
    // Draw GUI is in the "on" position by default
    drawGui = true;
    
    //Telling the noise image how big it should be
    noiseImage.allocate( resolution, resolution, OF_IMAGE_GRAYSCALE );
    
}

//--------------------------------------------------------------
void ofApp::update(){
    {
        //Moves the noise up, down, right and left.
        if( ofGetKeyPressed(OF_KEY_LEFT)  )  { noiseStartX += 5; }
        if( ofGetKeyPressed(OF_KEY_RIGHT ) ) { noiseStartX -= 5; }
        if( ofGetKeyPressed(OF_KEY_UP)  )    { noiseStartY += 5; }
        if( ofGetKeyPressed(OF_KEY_DOWN ) )  { noiseStartY -= 5; }
        
        float time = 0.0f; //Not sure
        if( animate ) time = ofGetElapsedTimef(); //animates the image over time
        
        //represents pixels data on the CPU as opposed to an ofTexture which represents pixel data on the GPU. They can easily be made inter-operational though:
        ofPixelsRef pixels = noiseImage.getPixelsRef(); //gets the pixel reference
        
        int tmpIndex = 0; //creates a temporary index
        for( int y = 0; y < noiseImage.getHeight(); y++ ) //for loop for the heigh
        {
            for( int x = 0; x < noiseImage.getWidth(); x++ ) //for loop for the width
            {
                // We're grabbing a single reading from the noise function here, but we can also add together more
                // readings at different frequencies to make more complex patterns
                float tmpNoise = ofNoise( (noiseStartX + x) / noiseFrequency, (noiseStartY + y) / noiseFrequency, time );
                
                pixels[tmpIndex] = tmpNoise * 255.0f; //not sure
                tmpIndex++;
            }
        }
        
        if( doThreshold)
        {
            threshold( false ); // Threshold in the "off" position
        }
        
        noiseImage.update(); // uploads the new pixels to the gfx card
    }
}

//--------------------------------------------------------------
void ofApp::threshold( bool _upload ){
    
    ofPixelsRef pixels = noiseImage.getPixelsRef(); //Looking at the noise image and getting all the noise pixels. The ref means give me the reference to where the pixels are located
    
    int tmpIndex = 0; //pixel count
    
    // Go through all the pixels...
    for( int y = 0; y < noiseImage.getHeight(); y++ )
    {
        for( int x = 0; x < noiseImage.getWidth(); x++ )
        {
            if( pixels[tmpIndex] >= thresholdLow && pixels[tmpIndex] <= thresholdHigh )
            {
                pixels[tmpIndex] = 255;
            }
            else
            {
                pixels[tmpIndex] = 0;
            }
            
            if( invert )
            {
                pixels[tmpIndex] = 255 - pixels[tmpIndex];
            }
            
            tmpIndex++; //...increasing by one each time we go through the loop
        }
    }
    
    
    if( _upload )
    {
        noiseImage.update(); //updates the noise image
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient( ofColor(0), ofColor(40), OF_GRADIENT_CIRCULAR ); //loads the background gradient
    
    //Scales the window and draws it
    ofRectangle imageRect(30,0,noiseImage.getWidth(), noiseImage.getHeight() );
    imageRect.scaleTo( ofRectangle(0,0,ofGetWidth(),ofGetHeight()) );
    noiseImage.draw( imageRect );
    
    if( drawGui ) //if draw GUI is called...
    {
        gui.draw(); //...draw the GUI
    }
    
}

//--------------------------------------------------------------
void ofApp::resolutionChanged( int& _res )
{
    noiseImage.allocate( _res, _res, OF_IMAGE_GRAYSCALE ); //allocates the image in greyscale
}

//--------------------------------------------------------------
void ofApp::keyPressed(int _key){
    
    //Toggles full screen
    if( _key == 'f' )
    {
        ofToggleFullscreen();
    }
    
}

