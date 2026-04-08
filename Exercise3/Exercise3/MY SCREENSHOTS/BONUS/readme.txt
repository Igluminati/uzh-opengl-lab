For the bonus task, I've implemented a spotlight instead of the point light.

It works by checking if each fragment is inside a cone. I've used an inner cutoff angle of 15° and an outer one of 25° to get a soft edge.

The intensity fades smoothly between these two angles so it doesn't look harsh. Outside the cone, you've only got the ambient light so things aren't completely black.

I've also animated the spotlight direction so it sweeps around the scene in a circle.
