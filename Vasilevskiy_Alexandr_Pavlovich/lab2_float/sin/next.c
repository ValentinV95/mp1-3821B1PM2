float next(float pred, int i, float x)
{
	return pred * x / i;
}
float next_cos(float pred, int i, float x)
{
	return pred * x * x / (2 * i * (2 * i - 1));
}
float next_sin(float pred, int i, float x)
{
	return pred * x * x / (2 * i * (2 * i + 1));
}