// Axis indexes;
X = 0; Y = 1; Z = 2;

FalconScale = 2;
FalconMOffset = [0,-2.41,0]; // Relative to FalconTop
FalconBOffset = [0.3,0,-3]; // Relative to FalconTop

FalconOffset = [FalconScale * 8.2, FalconScale * -1.1, FalconScale * 1.5]; // To Centre the Falcon
//ArduinoOffset = [0, 15+9.25, FalconScale * FalconBOffset[Z]/2];   // Relative to centred falcon
ArduinoOffset = [18, 5, 5.6];   // Relative to centred falcon
LedOffset = [-15.5, -10.5, 9.5];   // Relative to centred falcon

//echo( "Falcon at ", FalconScale, "x is ", (FalconScale * 95), " long, ", (FalconScale*70), " wide and ", (FalconScale*22), " tall" );
// scalebar();
difference() {
union() {
translate(FalconOffset) falcon(true,false,false);
//translate(ArduinoOffset) rotate([180,0,180]) arduino();
//translate(LedOffset) shiftbrite();
}
translate(ArduinoOffset) rotate([180,0,180]) arduino_cutout();
translate(LedOffset) shiftbrite_cutout();
}

module arduino_cutout() {
  cube( [45, 20.5, 4.8] ); 
}

module shiftbrite_cutout() {
  union() {
    shiftbrite();
    translate([0,0,-10]) cube([31,21,11.4]);
  }
}

module arduino() {
  Board = [43.5, 18.5, 4.8];
  Usb = [9.5, 7.6, 3.75];
  Pins = [5, 7.5, 8.25];
  PinsWithSpace = [Pins[X]+3, Pins[Y]+3, Pins[Z]+2];
  
  UsbOffset = [Board[X] - (Usb[X] - 1.9), centre(Board, Usb, Y), Board[Z]];
  PinsOffset = [0, centre(Board, PinsWithSpace, Y), Board[Z]];

  color( "Black", 0.8) {
    cube( Board ); 
    translate( UsbOffset ) cube( Usb );
    translate( PinsOffset ) cube( PinsWithSpace );
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
  
  color( "Black", 1 ){
    cube(Board);
    translate( LedbaseOffset ) cube( Ledbase );
    translate( LeddomeOffset ) sphere( r=Leddome/2, $fn=20 );
  }
  color ("White", 1) {
    translate( Pin1Offset ) cube( Pins );
    translate( Pin2Offset ) cube( Pins );
  }
}

// holes at given spacing
module holes(count, size, spacing) {
  union() {
    for (x = [0:count-1]) translate([spacing*x,0,0]) cylinder(h=10,r=(size/FalconScale)/2, $fn=40);
  }
}

module falcon(top, middle, bottom) {
  O = 0.5;
  
  scale(FalconScale)
    rotate([0,0,90]) {
      if (top) {
        //color( "Salmon", O) 
        difference() {
          import( "falcon2top_fixed.stl" );
          translate([15,9,5.64]) cube([15,5,3]);	// remove bobbles on right
          translate([-26,9,5.64]) cube([15,5,3]);	// remove bobbles on left
          translate([16,11.3,-4]) holes(3, 3, 5);	
          translate([-23.6,11.3,-4]) holes(3, 3, 5);	
          translate([1.2,-10,-4]) rotate([0,0,90]) holes(2, 3, 5);
          translate([-4.9,23,-2]) rotate([-8,0,0]) holes(2, 5, 12);
        }
      }
      if (middle) {
//      color( "DarkSalmon", O) 
        translate(FalconMOffset) rotate([0,180,0]) import( "falcon2middle_fixed.stl" );
      }
      if (bottom) {
//      color( "Salmon", O);
        translate(FalconBOffset) rotate([0,180,0]) import( "falcon2bottom_fixed.stl" );
      }
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


