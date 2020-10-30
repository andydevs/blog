Iteration Efficiency

Iterating through a value and computing another value from that

Try to update that value directly

Example: Rotation

Iterate angle. Compute $sin$ from that angle.

$sin$ is expensive.

Given change in angle, compute change in $sin = cos$.

Track two values. sin and cos. $sin$ changes by $cos$. $cos$ changes by $-sin$.