//
//  main.cpp
//
//
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <chrono>


void display_func(void)
{
    /*　画面と、デプスバッファを消去 */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* ４角形を描く */
    glBegin(GL_QUADS);
    
    /* 左側の面 */
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0,  1.0,  -9.0);
    glVertex3f(-1.0,  1.0, -11.0);
    glVertex3f(-1.0, -1.0, -11.0);
    glVertex3f(-1.0, -1.0,  -9.0);
    
    /* 右側の面 */
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f( 1.0,  1.0,  -9.0);
    glVertex3f( 1.0,  1.0, -11.0);
    glVertex3f( 1.0, -1.0, -11.0);
    glVertex3f( 1.0, -1.0,  -9.0);
    
    /* 上 */
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f( 1.0, 1.0,  -9.0);
    glVertex3f( 1.0, 1.0, -11.0);
    glVertex3f(-1.0, 1.0, -11.0);
    glVertex3f(-1.0, 1.0,  -9.0);
    
    /* 下 */
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f( 1.0, -1.0,  -9.0);
    glVertex3f( 1.0, -1.0, -11.0);
    glVertex3f(-1.0, -1.0, -11.0);
    glVertex3f(-1.0, -1.0,  -9.0);
    glEnd();
    
    /* 画面更新 */
    glFlush();
}


/*
 *    ウインドウサイズ更新時の処理
 */
void reshape_func(int width, int height)
{
    /* 表示範囲設定 */
    glViewport(0, 0, width, height);
    
    /* 投影行列を設定する */
    glMatrixMode(GL_PROJECTION);
    
    /*座標変換行列の初期化 */
    glLoadIdentity();
    
    /* 投影範囲を設定 */
    glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 10000.0);
    
    glMatrixMode(GL_MODELVIEW);
}


/*
 *    main関数
 *        glutを使ってウインドウを作るなどの処理をする
 */
int main(int argc, char *argv[])
{
    
    /* glutの初期化 */
    glutInit(&argc, argv);
    
    /* 画面表示の設定                                        */
    /*（３Ｄ表示をするので、デプスバッファを使うように設定    */
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    
    /* ウインドウの初期サイズを指定 */
    glutInitWindowSize(300, 300);
    
    /* ウインドウを作る */
    glutCreateWindow("Sample 2");
    
    /* 画面更新用の関数を登録 */
    glutDisplayFunc(display_func);
    
    /* ウインドウのサイズ変更時の関数を登録 */
    glutReshapeFunc(reshape_func);
    
    /* デプスバッファを使うように設定 */
    glEnable(GL_DEPTH_TEST);
    
    /* イベント処理などを始める */
    glutMainLoop();
    
    return 0;
}


//void hoge(int value){
//    auto start = std::chrono::system_clock::now();
//    int in = 0;
//    for (int i = 0; i < 640; ++i) {
//        in += 1;
//    }
//    auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
//    auto dur = end - start;        // 要した時間を計算
//    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
//    cout << in << ":" << msec << "milli sec \n";
//    glutTimerFunc(1000 , hoge , 0);
//}
//
//void display(void)
//{
//    /*　画面と、デプスバッファを消去 */
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    /* ４角形を描く */
//    glBegin(GL_QUADS);
//
//    /* 左側の面 */
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex3f(-1.0,  1.0,  -9.0);
//    glVertex3f(-1.0,  1.0, -11.0);
//    glVertex3f(-1.0, -1.0, -11.0);
//    glVertex3f(-1.0, -1.0,  -9.0);
//
//    /* 右側の面 */
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f( 1.0,  1.0,  -9.0);
//    glVertex3f( 1.0,  1.0, -11.0);
//    glVertex3f( 1.0, -1.0, -11.0);
//    glVertex3f( 1.0, -1.0,  -9.0);
//
//    /* 上 */
//    glColor3f(0.0, 0.0, 1.0);
//    glVertex3f( 1.0, 1.0,  -9.0);
//    glVertex3f( 1.0, 1.0, -11.0);
//    glVertex3f(-1.0, 1.0, -11.0);
//    glVertex3f(-1.0, 1.0,  -9.0);
//
//    /* 下 */
//    glColor3f(1.0, 1.0, 1.0);
//    glVertex3f( 1.0, -1.0,  -9.0);
//    glVertex3f( 1.0, -1.0, -11.0);
//    glVertex3f(-1.0, -1.0, -11.0);
//    glVertex3f(-1.0, -1.0,  -9.0);
//    glEnd();
//
//    /* 画面更新 */
//    glFlush();
//}
//
//void init(void)
//{
//    glClearColor(0.0, 0.0, 1.0, 1.0);
//}
//
//int main(int argc, char *argv[])
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGBA);
//    glutCreateWindow(argv[0]);
//    glutDisplayFunc(display);
//    init();
////    glutTimerFunc(1000 , hoge , 0);
//    glutMainLoop();
//
//    return 0;
//}





