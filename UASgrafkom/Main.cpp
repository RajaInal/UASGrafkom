#include<windows.h>
#include<GL/glu.h>
#include<GL/glut.h>

//GLfloat T = 0; 
GLfloat cameraX = 0.0f, cameraY = 1.0f, cameraZ = 3.0f; //posisi kamera x, y, z
GLfloat teapotRotation = 0.0f; //variabel untuk kontrol rotasi teko
GLfloat ballScaleFactor = 1.0f; //variabel untuk kontrol skalasi bola
GLfloat torusRotation = 0.0f; //variabel untuk kontrol rotasi torus

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //definisikan properti lampu
    const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
    //end

    //setting properti lampu
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //end

    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0); //gluLookAt untuk perspektif kamera

    //glRotatef(T, 0, 1, 0); //rotasi dengan "T" di sumbu y

    //objek torus dan bola di tengah
    GLfloat torusColor[] = { 0.5, 0.0, 0.5, 1.0 }; //warna torus menggunakan RGB (ungu)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, torusColor); //set warna ambient dan diffuse
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f); //posisi dari torus
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); //rotasi 90 derajat melalui sumbu x
    glRotatef(torusRotation, 0, 1, 0); //rotasi dengan "torusRotation" melalui sumbu y
    glutSolidTorus(0.1, 0.8, 50, 50); //menggambar torus

    GLfloat ballColorUp[] = { 0.0, 1.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ballColorUp);
    glutSolidSphere(0.2, 50, 50); //menggambar bola dengan radius 0.2
    glPopMatrix();
    //end

    //objek lantai
    GLfloat floorColor[] = { 0.8, 0.8, 0.8, 1.0 }; //warna lantai menggunakan RGB (abu-abu)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushMatrix();
    glTranslatef(0, -0.9, 0); //posisi dari lantai
    glScalef(2, 0.01, 2); //ukuran dari lantai 
    glutSolidCube(1); //solidcube
    glPopMatrix();
    //end

    //objek bola diatas lantai
    GLfloat ballColor[] = { 0.0, 0.5, 0.8, 1.0 }; //warna bola menggunakan RGB (biru)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ballColor);
    glPushMatrix();
    glTranslatef(0, -0.7, 0); //posisi dari bola
    glScalef(ballScaleFactor, ballScaleFactor, ballScaleFactor); //skalasi bola menggunakan ballScaleFactor
    glutSolidSphere(0.2, 50, 50); //menggambar bola dengan radius 0.2
    glPopMatrix();
    //end

    //objek meja
    GLfloat tableColor[] = { 0.6, 0.3, 0.0, 1.0 }; //warna meja menggunakan RGB
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, tableColor);
    glPushMatrix();
    glScalef(1, 0.05, 1);
    glutSolidCube(1);
    glPopMatrix();
    //end

    //objek kaki meja
    GLfloat M[] = { 0,1,0,1 }; //warna kaki meja menggunakan RGB
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, M);

    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, -0.5, -0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, -0.5, 0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, -0.5, 0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();
    //end

    //objek teko
    GLfloat potColor[] = { 0.5, 0.5, 0.5, 1.0 }; //warna teko menggunakan RGB
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, potColor);
    glPushMatrix();
    glTranslatef(0, 0.25, 0);
    glRotatef(teapotRotation, 0, 1, 0); //rotasi teko terhadap sumbu y
    glutSolidTeapot(0.25); //radius teko 0.25
    glPopMatrix();
    //end

    glutSwapBuffers();
}

void update(int value) //fungsi update untuk torus
{
    torusRotation += 1.0f; //menambah nilai "torusRotation" sebanyak 1.0
    if (torusRotation > 360.0f) //menjaga nilai rotasi tidak melebihi 360
        torusRotation -= 360.0f; //kurang 360 jika melewati 360

    glutPostRedisplay(); //update tampilan baru 
    glutTimerFunc(25, update, 0); //fungsi update dipanggil setiap 25 miliseconds
}

void handleKeypress(unsigned char key, int x, int y) //fungsi keyboard untuk mengubah posisi kamera dan skalasi bola diatas lantai
{
    switch (key)
    {
    case 'w':
        cameraZ -= 0.1f; //gerakkan kamera ke depan sepanjang sumbu z
        break;
    case 's':
        cameraZ += 0.1f; //gerakkan kamera ke belakang sepanjang sumbu z
        break;
    case 'a':
        cameraX -= 0.1f; //gerakkan kamera ke kiri sepanjang sumbu x
        break;
    case 'd':
        cameraX += 0.1f; //gerakkan kamera ke kanan sepanjang sumbu x
        break;
    case 'i':
        ballScaleFactor += 0.1f; //menambah skalasi bola diatas lantai
        break;
    case 'k':
        ballScaleFactor -= 0.1f; //mengurangi skalasi bola diatas lantai
        if (ballScaleFactor < 0.1f) //menjaga nilai skalasi tidak dibawah 0.1
            ballScaleFactor = 0.1f; //nilai skalasi menjadi 0.1 jika dibawah 0.1
        break;
    case 27:
        exit(0); //exit run dengan tombol Esc
        break;
    }
    glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y) //fungsi keyboard untuk rotasi teko
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        teapotRotation += 5.0f; //rotasi teko berlawanan arah jarum jam
        break;
    case GLUT_KEY_RIGHT:
        teapotRotation -= 5.0f; //rotasi teko searah jarum jam
        break;
    }
    glutPostRedisplay();
}

void MyInit()
{
    glEnable(GL_DEPTH_TEST); //depth testing untuk buffer

    glMatrixMode(GL_PROJECTION); //atur mode matriks ke proyeksi
    glLoadIdentity(); //matriks identitas
    glFrustum(-1, 1, -1, 1, 2, 10); //menentukan perspektif proyeksi
    glMatrixMode(GL_MODELVIEW); //tampilan model mode matrix untuk transformasi

    glEnable(GL_LIGHTING); //mengaktifkan lighting kalkulasi
    glEnable(GL_LIGHT0); //mengaktifkan first light source

    //properti light source
    const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //cahaya yang tersebar merata tanpa arah
    const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //cahaya yang diterima permukaan
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //cahaya yang dipantulkan dari permukaan dengan sudut tertentu
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f }; //posisi sumber cahaya
    //end

    //set light source ke GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //end

    glutTimerFunc(25, update, 0); //fungsi update setiap 25 miliseconds
}

int main(int argC, char* argV[])
{
    glutInit(&argC, argV);
    glutInitWindowSize(600, 600); //ukuran window
    glutInitWindowPosition(100, 100); //posisi window
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("UAS GRAFKOM");
    MyInit(); //panggil MyInit
    glutDisplayFunc(Draw); //panggil Draw untuk render
    glutKeyboardFunc(handleKeypress); //panggil handleKeypress untuk keyboard standar
    glutSpecialFunc(handleSpecialKeypress); //panggil handleSpecialKeypress untuk keyboard spesial (arrow)

    glutMainLoop();
    return 0;
}