/*
Additional References:
  http://home.ubalt.edu/ntsbarsh/opre640a/partviii.htm#rCarpenterPr

How to compile and run this program.

#!/bin/bash
# 
if [ -f repo/commons-math-2.2/commons-math-2.2.jar ]; then
 echo "commons-math-2.2.jar exists... so we will use it."
else

 echo "Did not find commons-math-2.2.jar so downloading"
 mkdir -p repo
 cd repo
 wget http://download.nextag.com/apache//commons/math/binaries/commons-math-2.2.tar.gz
 tar -xzf *.gz
 cd ..
fi
mkdir -p classes
javac -d classes -classpath repo/commons-math-2.2/commons-math-2.2.jar ApacheMath.java
java  -classpath repo/commons-math-2.2/commons-math-2.2.jar:classes ApacheMath



 */





import org.apache.commons.math.optimization.linear.LinearObjectiveFunction;
import org.apache.commons.math.optimization.linear.SimplexSolver;
import org.apache.commons.math.optimization.linear.LinearConstraint;
import org.apache.commons.math.optimization.RealPointValuePair;
import org.apache.commons.math.optimization.GoalType;
import org.apache.commons.math.optimization.linear.Relationship;


import java.util.ArrayList;
import java.util.Collection;

import org.apache.commons.math.optimization.GoalType;
import org.apache.commons.math.optimization.OptimizationException;
import org.apache.commons.math.optimization.RealPointValuePair;





public class ApacheMath {

    public static void main(String[] args) throws Exception    {

	/*

	  MIN -2x + y - 5
	  S.T.
	  x + 2y <= 6
	  3x + 2y <= 12
	  y >= 0
	 */
	
	// describe the optimization problem
	LinearObjectiveFunction f = new LinearObjectiveFunction(new double[] { -2, 1 }, -5);
	Collection<LinearConstraint> constraints = new ArrayList<LinearConstraint>();
	constraints.add(new LinearConstraint(new double[] { 1, 2 }, Relationship.LEQ, 6));
	constraints.add(new LinearConstraint(new double[] { 3, 2 }, Relationship.LEQ, 12));
	constraints.add(new LinearConstraint(new double[] { 0, 1 }, Relationship.GEQ, 0));

	// create and run the solver
	SimplexSolver solver = new SimplexSolver();
	RealPointValuePair solution =  solver.optimize(f, constraints, GoalType.MINIMIZE, false);

	// get the solution
	double x = solution.getPoint()[0];
	double y = solution.getPoint()[1];
	double min = solution.getValue();

	System.out.printf("x= %f y= %f min= %f\n",x,y,min);


    }


}