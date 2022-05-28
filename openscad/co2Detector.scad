//$fn = 180;

plateWidth = 80;
plateLength = 120;
plateHeight = 1;

circleRadius = 30;
ledLength = 6;


controllerLength = 18.5; // Nano


module plate()
{
    h = 8;
    
    difference()
    {
        cube([plateWidth, plateLength, plateHeight+h]);
        translate([1, 1, plateHeight]) cube([plateWidth-2, plateLength-2, h]);
        translate([plateWidth-2, 5, 5]) cube([2, controllerLength, 4]);
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

    translate([plateWidth/2, plateLength-plateWidth/2, plateHeight])
    {
        difference()
        {
            cylinder(h = height, r = circleRadius+ledLength/2+2.5);
            cylinder(h = height, r = circleRadius+ledLength/2+1.5);
        }

        difference()
        {
            cylinder(h = height, r = circleRadius-ledLength/2-0.75);
            cylinder(h = height, r = circleRadius-ledLength/2-1.75);
        }
        
        translate([0, 0, height-0.25]) difference()
        {
            cylinder(h = 0.25, r = circleRadius+ledLength/2+1.5);
            cylinder(h = 0.25, r = circleRadius+ledLength/2+1.25);
        }

        translate([0, 0, height-0.25]) difference()
        {
            cylinder(h = 0.25, r = circleRadius-ledLength/2-0.5);
            cylinder(h = 0.25, r = circleRadius-ledLength/2-0.75);
        }
    }    
    
}

module displayHolder()
{
    w = 28;
    l = 28;
    height = 4;

    translate([plateWidth/2, plateLength-plateWidth/2-2, plateHeight+height/2]) difference()
    {
        cube([w+2, l+2, height], true);
        cube([w, l, height], true);
    }
    
    translate([plateWidth/2, plateLength-plateWidth/2-2, plateHeight+height-0.25/2]) difference()
    {
        cube([w, l, 0.25], true);
        cube([w-0.5, l-0.5, 0.25], true);
    }

}

module controllHolderNano()
{
    w = 44;
    l = controllerLength;
    height = 4;
    xPos = plateWidth-w-2;
    yPos = 4;

    translate([w/2+1+xPos, l/2+1+yPos, plateHeight+height/2]) difference()
    {
        cube([w+2, l+2, height], true);
        cube([w, l, height], true);
    }
    
    translate([w/2+1+xPos, l/2+1+yPos, plateHeight+height-0.25/2]) difference()
    {
        cube([w, l, 0.25], true);
        cube([w-0.5, l-0.5, 0.25], true);
    }

}

module sensorHolder()
{
    w = 23.5;
    l = 35.5;
    height = 4;
    xPos = 4;
    yPos = 4;

    translate([w/2+1+xPos, l/2+1+yPos, plateHeight+height/2]) difference()
    {
        cube([w+2, l+2, height], true);
        cube([w, l, height], true);
    }
    
    translate([w/2+1+xPos, l/2+1+yPos, 0.25/2]) difference()
    {
        cube([w, l, 0.25], true);
        cube([w-0.5, l-0.5, 0.25], true);
    }

    translate([w/2+1+xPos, l/2+1+yPos, plateHeight+height-0.25/2]) difference()
    {
        cube([w, l, 0.25], true);
        cube([w-0.5, l-0.5, 0.25],true);
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
controllHolderNano();
sensorHolder();