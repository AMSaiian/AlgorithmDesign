def alpha_beta(state, depth, alpha, beta, is_maximizing):
    state.evaluate_state()
    if depth == 0 or not state.create_child_states():
        return state
    if is_maximizing:
        best_value = -float('inf')
        best_state = None
        for child in state.create_child_states():
            value = alpha_beta(child, depth - 1, alpha, beta, False).evaluation
            if value > best_value:
                best_value = value
                best_state = child
            alpha = max(alpha, best_value)
            if beta <= alpha:
                break
        return best_state
    else:
        best_value = float('inf')
        best_state = None
        for child in state.create_child_states():
            value = alpha_beta(child, depth - 1, alpha, beta, True).evaluation
            if value < best_value:
                best_value = value
                best_state = child
            beta = min(beta, best_value)
            if beta <= alpha:
                break
        return best_state
