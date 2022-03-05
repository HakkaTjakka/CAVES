# Test.

Create 1.12.2 region files with help of shader(s).

This one is rather complex. What goes very fast is calculating the 'paths' of some sine waveform 'tubes' running around the region file.

Its done by some (random) formulas that form a function based on x,y and z coord. VAL=f(X,Y,Z)

Then, when doing the same calculation for VAL=f(X+1,Y,Z), VAL=f(X,Y+1,Z), VAL=f(X,Y,Z+1).

A little bit like this:

    #include <somestuff>

    bool calculate(ivec3 pos) {
        int p[4];
        for (int n=0; n<4; n++) {
            float x=pos.x+(n==1);
            float y=pos.y+(n==2);
            float z=pos.z+(n==3);
            p[n]=int( 256.0+250.0*( sin( (x-256.0)/70.0 + sin( (z-200.0)/54.0 )/3.0 + sin( (y-100.0)/44.0 )/5.0 ) ) );
        }

        if ( !(     (p[0]>pos.x && p[1]>pos.x  && p[2]>pos.x  && p[3]>pos.x) ||
                    (p[0]<pos.x && p[1]<pos.x  && p[2]<pos.x  && p[3]<pos.x)) ) {
                    return true;
        }
        return false;
    }

    int main() {
        ivec3 pos;
        bool hit;

        for (pos.x=0; pos.x<512; pos.x++) {
            for (pos.y=0; pos.y<256; pos.y++) {
                for (pos.z=0; pos.z<512; pos.z++) {
                    hit=calculate(pos);
                }
            }
        }
    }



Of course you can calculate a whole array[512][256]512] before, it saves you 75% of calculations.

Then the same can be done in the GPU with a fragment shader.

The example here shown then creates arround every 'hit' a sphere, so you get a big tube following the path of the function.

The crux here you do NOT calculate a X,Y,Z position out of a formula, but have 3 loops (for X,Y and Z), and then determine wether the position is on the path or not. Maybe it also works with only 2 calculations, like f(X,Y,Z) and f(X+1,Y+1,Z+1), or (now you get more hits around one point in space, so cubes are connected) with f(X-dist,Y,Z) <> f(X+dist,Y,Z), f(X,Y-dist,Z)  <> f(X,Y+dist,Z), f(X,Y,Z-dist) <> f(X,Y,Z+dist).

Aim of the game is to use GPU shaders to do (very) fast calculations to create region files.
This example is not realy fast, because for every 'hit' it generates a 3d sphere with a diameter of 35 blocks around it, using up 35 shader calls.

I've published this for now to give you some idea about how shaders can speed up things. When not using complex algoritms like in this example a region file is created within the blink of an eye. Leaving lightning/compressing/saving as main time factor.

Next will be some examples to create (simple) shapes and/or region files, and do some editing with them. Realtime displaying in 3d (shaders also), and edit functions with help of shaders. Like ultrafast merging/subtraction / transforming / logical functions etc.

It would be nice feeding the calculated result directly to the beast in Java. But for that i'm working on a fast geometry shader using only the voxels (cubes position, a ivec3, and some other data like block type).

What i'm also working on is (stuff like that already exists but i'm building own that is simple sfml/opengl/c++ compatible) is feeding (int/float/other) data through textures to the fragment shader(s), and outputting data the same way.
Because SFML does not support native OpenGL for that OpenGL functions will be written for that to. 
Like passing a (ivec3) array to the geometry shader that then calculates all visible faces ot the cubes.
If you like to help please let me know. I'm renting only one brain here.
