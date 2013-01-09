// Axis indexes;
X = 0; Y = 1; Z = 2;

FalconScale = 2;
FalconMOffset = [0,-2.41,0]; // Relative to FalconTop
FalconBOffset = [0.3,0,-3]; // Relative to FalconTop

FalconOffset = [FalconScale * 8.2, FalconScale * -1.1, FalconScale * 1.5]; // To Centre the Falcon
ArduinoOffset = [0, 0, FalconScale * FalconBOffset[Z]];   // Relative to centred falcon
LedOffset = [-15.5, -10.5, 9.5];   // Relative to centred falcon

//echo( "Falcon at ", FalconScale, "x is ", (FalconScale * 95), " long, ", (FalconScale*70), " wide and ", (FalconScale*22), " tall" );
// scalebar();
translate(LedOffset) shiftbrite();
translate(ArduinoOffset) rotate([0,0,180]) arduino();
translate(FalconOffset) falcon();

module arduino() {
  Board = [43.5, 18.5, 4.8];
  Usb = [9.5, 7.6, 3.75];
  Pins = [5, 7.5, 8.25];
  
  UsbOffset = [Board[X] - (Usb[X] - 1.9), centre(Board, Usb, Y), Board[Z]];
  PinsOffset = [0, centre(Board, Pins, Y), Board[Z]];

  color( "Black", 0.8) {
    cube( Board ); 
    translate( UsbOffset ) cube( Usb );
    translate( PinsOffset ) cube( Pins );
  }
}

module shiftbrite() {
  Ledbase = [7.7,7.7,4.5];
  Leddome = 4.8;
  Board = [31,21,1.5];
  Pins = [16, 2.5, 12];
  
  LedbaseOffset = [centre(Board, Ledbase, X), centre(Board, Ledbase, Y), Board[Z]];
  LeddomeOffset = [Board[X]/2, Board[Y]/2, Ledbase[Z] + LedbaseOffset[Z]];
  Pin1Offset = [centre(Board, Pins, X), 1, -9];
  Pin2Offset = [centre(Board, Pins, X), Board[Y] - Pins[Y] - 1, -9];
  
  color( "Black", 0.8 ){
    cube(Board);
    translate( LedbaseOffset ) cube( Ledbase );
    translate( LeddomeOffset ) sphere( r=Leddome/2, $fn=20 );
    translate( Pin1Offset ) cube( Pins );
    translate( Pin2Offset ) cube( Pins );
  }
}

module falcon() {
  O = 0.5;
  
  scale(FalconScale)
    rotate([0,0,90]) {
      color( "Salmon", O) 
        import( "falcon2_top.stl" );
      color( "DarkSalmon", O) 
        translate(FalconMOffset) rotate([0,180,0]) import( "falcon2_middle.stl" );
      color( "Salmon", O) 
        translate(FalconBOffset) rotate([0,180,0]) import( "falcon2_bottom.stl" );
    }
}

module scalebar() {
  scale(FalconScale) {
    color("Blue", 1) {
      translate([-48,-1,-1]) cube([95, 2, 2]);
      rotate([0,0,90]) translate([-35,-1,-1]) cube([70, 2, 2]);
      rotate([0,90,0]) translate([-8,-1,-1]) cube([22, 2, 2]);
    }
  }
}

// Centre B in A along given axis
function centre( A, B, axis ) =
  (A[axis] - B[axis]) / 2;


