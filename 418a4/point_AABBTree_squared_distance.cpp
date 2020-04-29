#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  // according to the given pesudocode in given readme
  std::priority_queue<std::pair<double, std::shared_ptr<Object>>, std::vector<std::pair<double, std::shared_ptr<Object>>>, std::greater<std::pair<double, std::shared_ptr<Object>>>> Q;
  double d_l, d_r, temp_sqrd, dist;
  dist = point_box_squared_distance(query, root->box);
  Q.push(std::make_pair(dist, root));
  sqrd = std::numeric_limits<double>::max(); 

  while (!Q.empty()) {
    dist = Q.top().first;
    std::shared_ptr<Object> cur_tree = Q.top().second;
    Q.pop();

    if (dist < sqrd) {
      std::shared_ptr<Object> type_filter = std::dynamic_pointer_cast<AABBTree>(cur_tree);
      if (type_filter == nullptr) {
        std::shared_ptr<Object> t_desc;
        if (cur_tree->point_squared_distance(query, min_sqrd, max_sqrd, temp_sqrd, t_desc)) {
          if (temp_sqrd < sqrd) {
            sqrd = temp_sqrd;
            descendant = cur_tree;
          }
        }
      } else {
        if (std::static_pointer_cast<AABBTree>(cur_tree)->left != nullptr) {
          d_l = point_box_squared_distance(query, std::static_pointer_cast<AABBTree>(cur_tree)->left->box);
          Q.push(std::make_pair(d_l, std::static_pointer_cast<AABBTree>(cur_tree)->left));
        }
        if (std::static_pointer_cast<AABBTree>(cur_tree)->right != nullptr) {
          d_r = point_box_squared_distance(query, std::static_pointer_cast<AABBTree>(cur_tree)->right->box);
          Q.push(std::make_pair(d_r, std::static_pointer_cast<AABBTree>(cur_tree)->right));
        }
      }
    }
  }
  
  return sqrd != std::numeric_limits<double>::max();
  ////////////////////////////////////////////////////////////////////////////
}
