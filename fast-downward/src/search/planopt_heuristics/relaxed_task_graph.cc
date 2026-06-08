#include "relaxed_task_graph.h"

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

namespace planopt_heuristics {
RelaxedTaskGraph::RelaxedTaskGraph(const TaskProxy &task_proxy)
    : relaxed_task(task_proxy),
      variable_node_ids(relaxed_task.propositions.size()) {
    /*
      TODO: add your code for exercise 2 (b) here. Afterwards
        - variable_node_ids[i] should contain the node id of the variable node for variable i
        - initial_node_id should contain the node id of the initial node
        - goal_node_id should contain the node id of the goal node
        - the graph should contain precondition and effect nodes for all operators
        - the graph should contain all necessary edges.
    */

    // #### exercise 2(b)
    // 1. OR node for every proposition
    for (size_t i = 0; i < relaxed_task.propositions.size(); i++) {
        variable_node_ids[i] = graph.add_node(NodeType::OR);
    }

    // 2. Initial-state AND node (no successors → trivially forced true at the start)
    initial_node_id = graph.add_node(NodeType::AND);
    for (PropositionID id : relaxed_task.initial_state) {
        graph.add_edge(variable_node_ids[id], initial_node_id);
    }

    // 3. Goal AND node — forced true when every goal proposition is achievable
    goal_node_id = graph.add_node(NodeType::AND);
    for (PropositionID id : relaxed_task.goal) {
        graph.add_edge(goal_node_id, variable_node_ids[id]);
    }

    // 4. One AND node per operator (direct_cost = op.cost set in exercise 2c)
    for (const RelaxedOperator &op : relaxed_task.operators) {
        NodeID op_node = graph.add_node(NodeType::AND, op.cost);
        for (PropositionID pre : op.preconditions) {
            graph.add_edge(op_node, variable_node_ids[pre]);
        }
        for (PropositionID eff : op.effects) {
            graph.add_edge(variable_node_ids[eff], op_node);
        }
    }
    // #### end exercise 2(b)
}

void RelaxedTaskGraph::change_initial_state(const State &state) {
    // Remove all initial edges that where introduced for relaxed_task.initial_state.
    for (PropositionID id : relaxed_task.initial_state) {
        graph.remove_edge(variable_node_ids[id], initial_node_id);
    }
    // Switch initial state of relaxed_task
    relaxed_task.initial_state = relaxed_task.translate_state(state);

    // Add all initial edges for relaxed_task.initial_state.
    for (PropositionID id : relaxed_task.initial_state) {
        graph.add_edge(variable_node_ids[id], initial_node_id);
    }
}

bool RelaxedTaskGraph::is_goal_relaxed_reachable() {
    // Compute the most conservative valuation of the graph and use it to
    // return true iff the goal is reachable in the relaxed task.

    // #### exercise 2(b)
    graph.most_conservative_valuation();
    return graph.get_node(goal_node_id).forced_true;
    // #### end exercise 2(b)
}

int RelaxedTaskGraph::additive_cost_of_goal() {
    // Compute the weighted most conservative valuation of the graph and use it
    // to return the h^add value of the goal node.

    // TODO: add your code for exercise 2 (c) here.
    return -1;
}

int RelaxedTaskGraph::ff_cost_of_goal() {
    // TODO: add your code for exercise 2 (e) here.
    return -1;
}

}
