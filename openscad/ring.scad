numberLed = 16;
circleRadius = 30;
ledHeight = 1;
ledLength = 6;
ringHeight = 2;

displayLength = 15;
displayWidth = 27;
displayHeight = 2;
displayPCBLength = 28;
displayPCBWidth = 28;
displayPCBHeight = 1;

$fn = 180;

module ring()
{
    translate([0, 0, ledHeight]) difference()
    {
        cylinder(h = ringHeight, r = circleRadius+ledLength/2+2);
        cylinder(h = ringHeight, r = circleRadius-ledLength/2-1.5);
    }

    for (i = [0:360/numberLed:360]) 
        rotate([0, 0, i]) translate([0, circleRadius, ledHeight/2]) cube([ledLength, ledLength, ledHeight], true);
}

module display()
{
    union()
    {
        translate([0, 0, displayHeight/2]) cube([displayWidth, displayLength, displayHeight], true);
        translate([0, -2, displayHeight/2+displayPCBHeight/2]) cube([displayPCBWidth, displayPCBLength, displayPCBHeight], true);
    }
}

module sensor()
{
    translate([-20, -55, ledHeight/2]) cube([23.5, 35.5, ledHeight], true);
}

module displayHolder()
{
    height = 4;

    difference()
    {
        translate([0, -2, ledHeight+height/2]) cube([displayPCBWidth+1, displayPCBLength+1, height], true);
        translate([0, -2, ledHeight+height/2]) cube([displayPCBWidth, displayPCBLength, height], true);
    }
}

module ringHolder()
{
    height = 4;
    
    translate([0, 0, ledHeight]) difference()
    {
        cylinder(h = height, r = circleRadius+ledLength/2+2);
        cylinder(h = height, r = circleRadius+ledLength/2+1.5);
    }
    translate([0, 0, ledHeight]) difference()
    {
        cylinder(h = height, r = circleRadius-ledLength/2-1);
        cylinder(h = height, r = circleRadius-ledLength/2-1.5);
    }
}

module controllHolder()
{
    height = 4;
    
    translate([0, 0, ledHeight+height/2]) difference()
    {
        cube([19.5, 45, height], true);
        cube([18.5, 44, height], true);
    }
}

module sensorHolder()
{
    height = 4;

    translate([-20, -55, ledHeight+height/2])  difference()
    {    
        cube([24.5, 36.5, height], true);
        cube([23.5, 35.5, height], true);
    }
}

height = 1;

difference()
{
    translate([0, -20, height/2]) cube([80, 120, height], true);
    ring();
    display();
    sensor();
}

displayHolder();
ringHolder();
sensorHolder();
translate([27, -55, 0]) controllHolder();