#include "newton_root_finder.hpp"
#include "types.hpp"

namespace odes {

newton_root_finder::newton_root_finder(newton_root_finder_params_t params)
    : params_(std::move(params))
{
}

vector_t newton_root_finder::solve(multi_function_t func, vector_t initial)
{
    vector_t result = initial;
    vector_t tmp    = initial;

    for (integer_t i = 0; i < params_.max_interations; ++i) {
        matrix_t m = params_.jacoby_matrix_evaluator->evaluate(func, tmp);
        vector_t b = m * tmp - func(tmp);

        result = params_.matrix_solver->solve(m, b);

        if (boost::numeric::ublas::norm_2(tmp - result) < params_.precision) {
            break;
        }
        std::swap(result, tmp);
    }

    return result;
}

}
