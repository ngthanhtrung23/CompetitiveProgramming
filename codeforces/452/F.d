import std.algorithm;
import std.array;
import std.container;
import std.conv;
import std.exception;
import std.functional;
import std.math;
import std.numeric;
import std.range;
import std.stdio;
import std.string;
import std.typecons;
import core.bitop;

bool solve (int [] p)
{
	static immutable int MAX_LIMIT = 60;

	int n = to !(int) (p.length);

	auto q = new int [n];
	foreach (i; 0..n)
	{
		q[p[i]] = i;
	}

	foreach (i; 0..n)
	{
		int k = 0;
		int lim = min (i + 1, n - i);
		if (lim <= 2 * MAX_LIMIT)
		{
			foreach (j; 1..lim)
			{
				if ((q[i - j] < q[i]) != (q[i + j] < q[i]))
				{
					return true;
				}
			}
		}
		else
		{
			foreach (j; 1..MAX_LIMIT)
			{
				if ((q[i - j] < q[i]) != (q[i + j] < q[i]))
				{
					return true;
				}
			}
			foreach (j; lim - MAX_LIMIT..lim)
			{
				if ((q[i - j] < q[i]) != (q[i + j] < q[i]))
				{
					return true;
				}
			}
		}
	}

	foreach (i; 0..n)
	{
		int lo = max (0, i - MAX_LIMIT);
		foreach_reverse (j; lo..i)
		{
			int k = p[i] * 2 - p[j];
			if (k < 0 || n <= k)
			{
				continue;
			}
			if (q[k] > i)
			{
				return true;
			}
		}

		int hi = min (n - 1, i + MAX_LIMIT);
		foreach (j; i + 1..hi + 1)
		{
			int k = p[i] * 2 - p[j];
			if (k < 0 || n <= k)
			{
				continue;
			}
			if (q[k] < i)
			{
				return true;
			}
		}
	}

	return false;
}

void main ()
{
	int n;
	while (readf (" %s", &n) > 0)
	{
		auto p = new int [n];
		foreach (ref x; p)
		{
			readf (" %s", &x);
		}
		p[] -= 1;
		writeln (solve (p) ? "YES" : "NO");
	}
}