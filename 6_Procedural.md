[TOC]

# 6. Procedural

## 6.1 Midpoint dicplacement

One of the most basic procedural algorithms. It's used to gradually change the randomness based on two initial values.

A typical recursive implementation:

```c#
public class MidpointDisplacement
{
  private const float DELTA = 0.75F; //the degrading factor of randomness
  private System.Random randomizer;
  private float[] values; //Our class is basically a wrapper for this array
  
//EMBRACE URSELF FOR AWESOME C#-code
//A readonly-indexer, making it possible to access values through the //MidpointDisplacement instance like this: float foo = midpointDisplacement[i];
  public float this[int index] { get { return values[index]; } }
//make size a property of the midpoint displacement.
  public int size { get { return values.Length; } }

/// Constructor for a new midpoint displacement
/// seed - the randomizer seed.
/// detail - iterations, causing finer details.
/// randomness - initail alpha value.
  public MidpointDisplacement(int seed, int detail, float randomness)
  {
    randomizer = new System.Random(seed); //initialize randomizer with a seed.
    values = new float[1+(int)Math.Pow(2,detail)]; //1+2^n = #points per iteration
    DoMidpointDisplacement(randomness);
  }
  private void DoMidpointDisplacement(float randomness)
  {
    values[0] = randomizer.NextFloat();
    values[size-1] = randomizer.NextFloat();
    Step(0, size-1, randomness * DELTA);
  }
  /// find the index in between
  /// i0 - first index
  /// i1 - second index
  private void Step(int i0, int i1, float alpha)
  {
    int midIndex = ( i0 + i1 ) / 2; //The index between the two indices
    float avg = ( values[i0] + values[i1] ) * 0.5f; //average previous
    values[midIndex] = avg + randomizer.NextFloat() * alpha; //assign midpoint
    if ( (midIndex - i0) > 1 ) //if there is space for another iteration
   	{
      Step(i0, midIndex, alpha * DELTA); //step into lower part, i.e. next iteration
      Step(midIndex, i1, alpha * DELTA); //step into higher part, i.e. next iteration
   	}
  }
}
```

## 6.2 Diamond Square
## 6.3 Perlin Noise
## 6.4 Bolzmann fields
