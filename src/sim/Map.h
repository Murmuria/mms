#pragma once

#include <QMap>
#include <QOpenGLBuffer> 
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram> 
#include <QOpenGLTexture> 
#include <QOpenGLVertexArrayObject> 
#include <QOpenGLWidget>
#include <QResizeEvent>
#include <QVector>

#include "Lens.h"
#include "Model.h"

namespace mms {

class Map : public QOpenGLWidget, protected QOpenGLFunctions {
    
    // NOTE: Inheriting from QOpenGLFunctions allows
    // us to call the OpenGL functions directly

	Q_OBJECT

public:

    Map(const Model* model, Lens* lens, QWidget* parent = 0);

    QVector<QString> getOpenGLVersionInfo();

protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
	void resizeEvent(QResizeEvent* event);

private:

    // Logger of OpenGL warnings and errors
	QOpenGLDebugLogger m_openGLLogger;
	void initOpenGLLogger();

    // The maze-and-mouse model
    const Model* m_model;

    // TODO: MACK - figure out how to make const
    // The maze, as perceived by the mouse algo
    Lens* m_lens;

    // The window size, in pixels
    int m_windowWidth;
    int m_windowHeight;

    // Polygon program variables
	QOpenGLShaderProgram m_polygonProgram;
	QOpenGLVertexArrayObject m_polygonVAO;
	QOpenGLBuffer m_polygonVBO;

    // Texture program variables
	QOpenGLTexture* m_textureAtlas;
	QOpenGLShaderProgram m_textureProgram;
	QOpenGLVertexArrayObject m_textureVAO;
	QOpenGLBuffer m_textureVBO;

    // Initialize the graphics
    void initPolygonProgram();
    void initTextureProgram();

    // Drawing helper methods
    void repopulateVertexBufferObjects();
    void drawFullAndZoomedMaps(
        const Coordinate& currentMouseTranslation,
		const Angle& currentMouseRotation,
        QOpenGLShaderProgram* program,
		QOpenGLVertexArrayObject* vao,
		int vboStartingIndex,
		int count);
};

} // namespace mms
