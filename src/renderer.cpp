
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
    glDrawArrays(GL_TRIANGLES, 0, model.vertex_count);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

}
