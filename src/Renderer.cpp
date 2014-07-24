#include <Renderer.h>
#include <GLheaders.h>


void renderWireframe(const Mesh& mesh) {
    mesh.material.use();

    glBegin(GL_LINES);
    for (auto& e : mesh.edges) {
        glVertex3d(mesh.vertices[e.from].position.x, mesh.vertices[e.from].position.y, mesh.vertices[e.from].position.z);
        glVertex3d(mesh.vertices[e.to].position.x, mesh.vertices[e.to].position.y, mesh.vertices[e.to].position.z);
    }
    glEnd();
}

void renderSolid(const Mesh& mesh) {
    mesh.material.use();

    glBegin(GL_TRIANGLES);
    for (auto& f : mesh.facets) {
        // glNormal3d(f.normal.x, f.normal.y, f.normal.z);
        glTexCoord2d(f.textCoords[0].x, f.textCoords[0].y);
        glNormal3d(mesh.vertices[f.a].normal.x, mesh.vertices[f.a].normal.y, mesh.vertices[f.a].normal.z);
        glVertex3d(mesh.vertices[f.a].position.x, mesh.vertices[f.a].position.y, mesh.vertices[f.a].position.z);

        // glNormal3d(f.normal.x, f.normal.y, f.normal.z);
        glTexCoord2d(f.textCoords[1].x, f.textCoords[1].y);
        glNormal3d(mesh.vertices[f.b].normal.x, mesh.vertices[f.b].normal.y, mesh.vertices[f.b].normal.z);
        glVertex3d(mesh.vertices[f.b].position.x, mesh.vertices[f.b].position.y, mesh.vertices[f.b].position.z);

        // glNormal3d(f.normal.x, f.normal.y, f.normal.z);
        glTexCoord2d(f.textCoords[2].x, f.textCoords[2].y);
        glNormal3d(mesh.vertices[f.c].normal.x, mesh.vertices[f.c].normal.y, mesh.vertices[f.c].normal.z);
        glVertex3d(mesh.vertices[f.c].position.x, mesh.vertices[f.c].position.y, mesh.vertices[f.c].position.z);
    }
    glEnd();
}

void renderMesh(const Mesh& mesh) {
    switch (mesh.material.fillMode) {
        case FillMode::Wireframe:
            renderWireframe(mesh);
            break;
        case FillMode::Solid:
            renderSolid(mesh);
            break;
        default:
            break;
    }
}


void setupLight(const PointLight& light, int lightIndex) {
    glEnable(GL_LIGHT0 + lightIndex);
    glLightfv(GL_LIGHT0 + lightIndex, GL_AMBIENT, &(light.ambient * light.intensity)[0]);
    glLightfv(GL_LIGHT0 + lightIndex, GL_DIFFUSE, &(light.diffuse * light.intensity)[0]);
    glLightfv(GL_LIGHT0 + lightIndex, GL_SPECULAR, &(light.specular * light.intensity)[0]);

    glLightfv(GL_LIGHT0 + lightIndex, GL_POSITION, new GLfloat[4] {
        static_cast<GLfloat>(light.position.x),
        static_cast<GLfloat>(light.position.y),
        static_cast<GLfloat>(light.position.z),
        1.0f
    });
}

void disableLight(int lightIndex) {
    glDisable(GL_LIGHT0 + lightIndex);
}

void Renderer::render(const Scene& scene, Camera& camera) {
    camera.set();

    glEnable(GL_LIGHTING);

    int lightIndex = 0;
    for (auto& pointLight : scene.pointLights)
        setupLight(pointLight, lightIndex++);

    for (auto& mesh : scene.meshes) {
        glPushMatrix();
        glMultMatrixf(&mesh.modelToWorldMatrix[0][0]);
        renderMesh(mesh);
        glPopMatrix();
    }

    for (int i = 0; i < scene.pointLights.size(); i++)
        disableLight(i);

    glDisable(GL_LIGHTING);
}
