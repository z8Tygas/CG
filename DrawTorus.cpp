void drawTorus(float R, float r, int slices, int stacks) {
    float arch_alpha = (2 * M_PI) / stacks, arch_beta = (2 * M_PI) / slices;
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;

    R = (R + r) / 2;
    r = R - r;


    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = (R + r * cos(arch_alpha * i)) * cos(arch_beta * j);
            x2 = (R + r * cos(arch_alpha * (i+1))) * cos(arch_beta * j);
            x3 = (R + r * cos(arch_alpha * (i+1))) * cos(arch_beta * (j+1));
            x4 = (R + r * cos(arch_alpha * i)) * cos(arch_beta * (j+1));

            y1 = r * sin(arch_alpha * i);
            y2 = r * sin(arch_alpha * (i+1));
            y3 = r * sin(arch_alpha * (i+1));
            y4 = r * sin(arch_alpha * i);

            z1 = (R + r * cos(arch_alpha * i)) * sin(arch_beta * j);
            z2 = (R + r * cos(arch_alpha * (i+1))) * sin(arch_beta * j);
            z3 = (R + r * cos(arch_alpha * (i+1))) * sin(arch_beta * (j+1));
            z4 = (R + r * cos(arch_alpha * i)) * sin(arch_beta * (j+1));

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x4, y4, z4);

            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);

        }
    }
    glEnd();
}
