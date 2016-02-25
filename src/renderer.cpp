
#include "renderer.hpp"

#include <glad/glad.h>

namespace jac {

void renderer::prepare()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer::render(const raw_model& model)
{
    glBindVertexArray(model.vao_id);
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, model.vertex_count, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

}
