$fn = 180;

plateWidth = 80;
plateLength = 120;
plateHeight = 1;

circleRadius = 30;
ledLength = 6;

module plate()
{
    difference()
    {
        cube([plateWidth, plateLength, plateHeight+7]);
        translate([1, 1, plateHeight]) cube([plateWidth-2, plateLength-2, 7]);
    }
}

module led()
{
    numberLed = 16;

    translate([plateWidth/2, plateLength-plateWidth/2, 0]) for (i = [0:360/numberLed:360]) 
        rotate([0, 0, i]) translate([0, circleRadius, plateHeight/2]) cube([ledLength, ledLength, plateHeight], true);
}

module display()
{
    w = 27;
    l = 15;
    
    translate([plateWidth/2, plateLength-plateWidth/2, plateHeight/2]) cube([w, l, plateHeight], true);
}

module sensor()
{
    w = 23.5;
    l = 35.5;
    
    translate([5, 5, 0]) cube([w, l, plateHeight]);
}

module ledHolder()
{
    height = 4;

    translate([plateWidth/2, plateLength-plateWidth/2, plateHeight]) difference()
    {
        cylinder(h = height, r = circleRadius+ledLength/2+2.25);
        cylinder(h = height, r = circleRadius+ledLength/2+1.25);
    }
    translate([plateWidth/2, plateLength-plateWidth/2, plateHeight]) difference()
    {
        cylinder(h = height, r = circleRadius-ledLength/2-0.75);
        cylinder(h = height, r = circleRadius-ledLength/2-1.75);
    }
}

module displayHolder()
{
    w = 28;
    l = 28;
    height = 4;

    difference()
    {
        translate([plateWidth/2, plateLength-plateWidth/2-2, plateHeight/2+height/2]) cube([w+2, l+2, height], true);
        translate([plateWidth/2, plateLength-plateWidth/2-2, plateHeight/2+height/2]) cube([w, l, height], true);
    }
}

module controllHolder()
{
    w = 18.5;
    l = 44;
    height = 4;
    
    translate([plateWidth-w-2-2, 2, plateHeight]) difference()
    {
        cube([w+2, l+2, height]);
        translate([1, 1, 0]) cube([w, l, height]);
    }
}

module sensorHolder()
{
    w = 23.5;
    l = 35.5;
    height = 4;

    difference()
    {
        translate([5-1, 5-1, plateHeight]) cube([w+2, l+2, height]);
        translate([5, 5, plateHeight]) cube([w, l, height]);
    }
}


difference()
{
    plate();
    led();
    display();
    sensor();
}

ledHolder();
displayHolder();
controllHolder();
sensorHolder();