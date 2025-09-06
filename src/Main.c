#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/PerlinNoise.h"


int Octaves = 7;
float Persistance = 500.0f;

void Setup(AlxWindow* w){
    PerlinNoise_Permutations_Init();

    AlxFont_Resize(&window.AlxFont,50,50);
}

void Update(AlxWindow* w){
    if(Stroke(ALX_KEY_UP).PRESSED){
        Octaves++;
    }
    if(Stroke(ALX_KEY_DOWN).PRESSED){
        Octaves--;
    }

    if(Stroke(ALX_KEY_W).PRESSED){
        Persistance *= 1.01f;
    }
    if(Stroke(ALX_KEY_S).PRESSED){
        Persistance *= 0.99f;
    }
    
    Clear(BLACK);

    RGA_Set(Time_Nano());

    PerlinNoise_Offset_Set(Octaves);
    PerlinNoise_Persistance_Set(Persistance);

    for (int y = 0; y < GetHeight(); y++) {
        for (int x = 0; x < GetWidth(); x++) {
            float px = (float)x;
            float py = (float)y;
            float n = PerlinNoise_2D_Get(px,py);
            
            n += 1.0;
            n /= 2.0;
            
            Draw(x,y,Pixel_toRGBA(n,n,n,1.0f));
        }
    }
    
    String str = String_Format("O:%d  P:%f",Octaves,Persistance);
    RenderCStrSize(str.Memory,str.size,0.0f,0.0f,RED);
    String_Free(&str);
}

void Delete(AlxWindow* w){
    
}

int main(){
    if(Create("Perlin Noise 2H",1800,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}