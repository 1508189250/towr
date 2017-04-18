/**
 @file    dynamic_constraint.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Dec 5, 2016
 @brief   Brief description
 */

#ifndef XPP_XPP_OPT_SRC_DYNAMIC_CONSTRAINT_H_
#define XPP_XPP_OPT_SRC_DYNAMIC_CONSTRAINT_H_

#include <memory>

#include <xpp/opt/linear_inverted_pendulum.h>
#include <xpp/time_discretization_constraint.h>

namespace xpp {
namespace opt {

class BaseMotion;
class EndeffectorLoad;
class EndeffectorsMotion;

class DynamicConstraint : public TimeDiscretizationConstraint {
public:
  using BaseMotionPtr = std::shared_ptr<BaseMotion>;
  using EEMotionPtr   = std::shared_ptr<EndeffectorsMotion>;
  using EELoadPtr     = std::shared_ptr<EndeffectorLoad>;

  DynamicConstraint (const OptVarsPtr& opt_vars, double T, double dt);
  virtual ~DynamicConstraint ();

private:
  BaseMotionPtr com_motion_;
  EEMotionPtr ee_motion_;
  EELoadPtr ee_load_;

  mutable LinearInvertedPendulum model_;

  int GetRow(int node, int dimension) const;

  virtual void UpdateConstraintAtInstance(double t, int k) const override;
  virtual void UpdateBoundsAtInstance(double t, int k) override;
  virtual void UpdateJacobianAtInstance(double t, int k) override;
};

} /* namespace opt */
} /* namespace xpp */

#endif /* XPP_XPP_OPT_SRC_DYNAMIC_CONSTRAINT_H_ */
