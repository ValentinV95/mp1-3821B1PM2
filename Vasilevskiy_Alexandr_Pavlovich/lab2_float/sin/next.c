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
float sum_in_order(float* arr, int len)
{
	float SUM = 0.0f;
	for (int i = 0; i < len; i++)
	{
		SUM += arr[i];
	}
	free(arr);
	return SUM;
}
float sum_from_the_end(float* arr, int len)
{
	float SUM = 0.0f;
	for (int i = len - 1; i >= 0; i--)
	{
		SUM += arr[i];
	}
	free(arr);
	return SUM;
}
float sum_in_pairs(float* arr, int len)
{
	float SUM = 0.0f, sum;
	for (int i = 1; i < len; i += 2)
	{
		sum = arr[i - 1] + arr[i];
		SUM += sum;
	}
	if (len % 2 == 1)
	{
		SUM += arr[len - 1];
	}
	free(arr);
	return SUM;
}