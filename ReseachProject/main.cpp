//
//  main.cpp
//
#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <chrono>
#include <sys/time.h>
#include <thread>
#include "Vector.h"//自前で用意したもの

static GLfloat rot_y, rot_x;    /* 立方体の回転角度 */
static GLfloat bgn_y, bgn_x;    /* ドラッグ開始時の回転角度 */
static int mouse_x, mouse_y;    /* ドラッグ開始時のマウスの位置 */
static GLuint cubelist;            /* 立方体のリスト */

GLfloat move = 1.0;



class Camera{
    public:
    VECTOR3 position = {0,0,20};
    VECTOR3 viewpoint = {0,0,0};
    
    void showDetail(){//デバッグ用関数
        printf("***show***\n");
        printf("position:(%f,%f,%f)\n",position.x,position.y,position.z);
        printf("viewpoint:(%f,%f,%f)\n",viewpoint.x,viewpoint.y,viewpoint.z);
    }
};

/*カメラオブジェクトのインスタンス化*/
Camera cam;

/*
 *    画面更新時の処理
 */
void display_func(void)
{
    /*　画面と、デプスバッファを消去 */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* 現在の座標系を保存 */
    glPushMatrix();
//    /* まず、座標系を画面の奥に移動 */
//    glTranslatef(0.0, 0.0, -15.0);
//
//    /* 回転 */
    glRotatef(rot_x, 1.0, 0.0, 0.0);
    glRotatef(rot_y, 0.0, 1.0, 0.0);
    
    /* 立方体の描画 */
    glCallList(cubelist);

    /* 座標系をもとに戻す */
    glPopMatrix();
    
    /* ダブルバッファのバッファを入れ替え、画面を更新 */
    glutSwapBuffers();
}


/*
 *    立方体のリストを作成
 */
GLuint make_cube(void)
{
    GLint list;
    
    /* 立方体の頂点 */
    static GLfloat vert[][4]={
        { 1.0,  1.0,  1.0},
        {-1.0,  1.0,  1.0},
        {-1.0, -1.0,  1.0},
        { 1.0, -1.0,  1.0},
        { 1.0,  1.0, -1.0},
        {-1.0,  1.0, -1.0},
        {-1.0, -1.0, -1.0},
        { 1.0, -1.0, -1.0},
    };
    
    /* 立方体の面の色 */
    static GLfloat color[][4]={
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 1.0, 1.0, 0.0},
        {1.0, 0.0, 1.0, 0.0},
        {1.0, 1.0, 0.0, 0.0},
    };
    
    /* 新しいリスト番号を取得 */
    list=glGenLists(1);
    
    /* 新しいリストを作成 */
    glNewList(list, GL_COMPILE);
    
    /* 立方体を描く */
    glBegin(GL_QUADS);
    glColor3fv(color[0]);
    glVertex3fv(vert[0]);
    glVertex3fv(vert[1]);
    glVertex3fv(vert[2]);
    glVertex3fv(vert[3]);
    
    glColor3fv(color[1]);
    glVertex3fv(vert[4]);
    glVertex3fv(vert[5]);
    glVertex3fv(vert[6]);
    glVertex3fv(vert[7]);
    
    glColor3fv(color[2]);
    glVertex3fv(vert[0]);
    glVertex3fv(vert[1]);
    glVertex3fv(vert[5]);
    glVertex3fv(vert[4]);
    
    glColor3fv(color[3]);
    glVertex3fv(vert[2]);
    glVertex3fv(vert[3]);
    glVertex3fv(vert[7]);
    glVertex3fv(vert[6]);
    
    glColor3fv(color[4]);
    glVertex3fv(vert[3]);
    glVertex3fv(vert[0]);
    glVertex3fv(vert[4]);
    glVertex3fv(vert[7]);
    
    glColor3fv(color[5]);
    glVertex3fv(vert[1]);
    glVertex3fv(vert[2]);
    glVertex3fv(vert[6]);
    glVertex3fv(vert[5]);
    
    glEnd();
    
    
    /* リスト作成終了 */
    glEndList();
    
    return list;
}

/*
 *    ウインドウサイズ更新時の処理
 */
void reshape_func(int width, int height)
{
    /* 表示範囲設定 */
    glViewport(0, 0, width, height);
    /* 投影方法設定 */
    glMatrixMode(GL_PROJECTION);
    /*座標変換行列の初期化 */
    glLoadIdentity();
    /* 投影範囲を設定 */
    glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 10000.0); //void glFrustum(l, r, b, t, n ,f)
    
    glMatrixMode(GL_MODELVIEW);
}

/*
 *    マウスクリック時の処理
 */
void mouse_func(int button, int stat, int x, int y)
{
    if(GLUT_DOWN==stat && GLUT_LEFT==button){
        /* マウスの左ボタンが押されたら、    */
        /* マウス位置を保存する             */
        mouse_x=x;
        mouse_y=y;
        bgn_y=rot_y;
        bgn_x=rot_x;
    }
}

/*
 *    マウスドラッグ時の処理
 */
void drag_func(int x, int y)
{
    /* 回転角度を求める */
    rot_x=(GLfloat)(y-mouse_y)+bgn_x;
    rot_y=(GLfloat)(x-mouse_x)+bgn_y;

    /* 回転角度が範囲内かチェック */
    if(90<rot_x){
        rot_x=90;
    }
    if(rot_x<-90){
        rot_x=-90;
    }

    /* 画面の描き換えを要求 */
    glutPostRedisplay();
}

/*
 * キーが押されたときの処理
 */
void key_func(unsigned char key, int x, int y)
{
    switch(toupper(key)){
        case 0x1b:    /* ＥＳＣキー */
            /* プログラムを終了 */
            exit(0);
            break;
        case 'P':    /* Ｑキー */
            cam.showDetail();
            break;
    }
}

/*
 *    特殊キーが押されたときの処理
 */
void skey_func(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_DOWN:    /* したキー *///ここの挙動は気をつける回転について考慮してない
            cam.position.z += move;//位置移動//
            cam.viewpoint.z += move;//視点移動//
            gluLookAt(0,0,move,
                      0,0,move-1,
                      0,1,0);
//            rot_x+=10;
            break;
        case GLUT_KEY_UP:    /* 上キー *///
            cam.position.z -= move;//位置移動//
            cam.viewpoint.z -= move;//視点移動//
            gluLookAt(0,0,-move,
                      0,0,-move-1,
                      0,1,0);
            break;
        case GLUT_KEY_LEFT:    /* 左キー */
//            rot_y+=10;
            cam.position.x -= move;//位置移動
            cam.viewpoint.x -= move;//視点移動
            gluLookAt(-move,0,0,
                      -move,0,-1,
                      0,1,0);
            break;
        case GLUT_KEY_RIGHT: /* 右キー */
//            rot_y-=10;
            cam.position.x += move;//位置移動
            cam.viewpoint.x += move;//視点移動
            gluLookAt(move,0,0,
                      move,0,-1,
                      0,1,0);
//            cam.showDetail();
            break;
    }
    
    /* 画面の描き換えを要求 */
    glutPostRedisplay();
}

void loop(){
    int j = 0;
    while(1){
        j += 1;
//        printf("fin:%d\n",j);
    }
}
/*
 *    main関数
 *        glutを使ってウインドウを作るなどの処理をする
 */
int main(int argc, char *argv[])
{
    std::thread t1(loop);
    /* glutの初期化 */
    glutInit(&argc, argv);
    
    /* 画面表示の設定 */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    /* ウインドウの初期サイズを指定 */
    glutInitWindowSize(300,300);
    
    /* ウインドウを作る */
    glutCreateWindow("glut window");
    
    /*初期視点の設定*/
    gluLookAt(cam.position.x,cam.position.y,cam.position.z, cam.viewpoint.x,cam.viewpoint.y,cam.viewpoint.z, 0,1,0);
    
    /* 画面更新用の関数を登録 */
    glutDisplayFunc(display_func);
    
    /* ウインドウのサイズ変更時の関数を登録 */
    glutReshapeFunc(reshape_func);
    
    /* キーボード入力用関数を登録 */
    glutKeyboardFunc(key_func);
    glutSpecialFunc(skey_func);
    
    /* マウス用関数を登録 */
    glutMotionFunc(drag_func);
    glutMouseFunc(mouse_func);
    
    /* デプスバッファを使うように設定 */
    glEnable(GL_DEPTH_TEST);
    
    /* リストを作成 */
    cubelist=make_cube();
    /* イベント処理などを始める */
    glutMainLoop();
    
    return 0;
}
