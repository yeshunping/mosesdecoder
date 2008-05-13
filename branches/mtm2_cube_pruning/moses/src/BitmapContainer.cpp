#include "BitmapContainer.h"
#include <utility>

SquarePosition *BackwardsEdge::m_invalid = NULL;

BackwardsEdge::BackwardsEdge(const BitmapContainer &prevBitmapContainer)
  : m_prevBitmapContainer(prevBitmapContainer)
	, m_queue()
{
}

const SquarePosition
BackwardsEdge::InvalidSquarePosition()
{
	if (BackwardsEdge::m_invalid == NULL) {
		BackwardsEdge::m_invalid = new SquarePosition(0.f, make_pair(-1, -1));
	}

	return *BackwardsEdge::m_invalid;
}

BackwardsEdge::~BackwardsEdge()
{
	// As we have created the square position objects we clean up now.
	for (size_t q_iter = 0; q_iter < m_queue.size(); q_iter++)
	{
		SquarePosition *ret = m_queue.top();
		delete ret;
		m_queue.pop();
	}
}

const BitmapContainer&
BackwardsEdge::GetBitmapContainer() const
{
	return m_prevBitmapContainer;
}

void
BackwardsEdge::Enqueue(int x, int y, float score)
{
	// We create a new square position object with the given values here.
	SquarePosition *chunk = new SquarePosition();
	chunk->first = score;
	chunk->second = make_pair(x, y);

	// And put it into the priority queue.
	m_queue.push(chunk);
}

SquarePosition
BackwardsEdge::Dequeue(bool keepValue)
{
	// Return the topmost square position object from the priority queue.
	// If keepValue is false (= default), this will remove the topmost object afterwards.
	if (!m_queue.empty()) {
		SquarePosition ret = *(m_queue.top());

		if (!keepValue) {
			m_queue.pop();
		}

		return ret;
	}
	
	return InvalidSquarePosition();
}

BitmapContainer::BitmapContainer(const WordsBitmap &bitmap)
  : m_bitmap(bitmap)
{
	m_hypotheses = OrderedHypothesisSet();
	m_edges = BackwardsEdgeSet();
}

BitmapContainer::~BitmapContainer()
{
	BackwardsEdgeSet::iterator e_iter;
	for (e_iter = m_edges.begin(); e_iter != m_edges.end(); ++e_iter)
	{
		delete *e_iter;
	}

	m_hypotheses.clear();
	m_edges.clear();
}
		
const WordsBitmap&
BitmapContainer::GetWordsBitmap()
{
	return m_bitmap;
}

const OrderedHypothesisSet&
BitmapContainer::GetHypotheses()
{
	return m_hypotheses;
}

const BackwardsEdgeSet&
BitmapContainer::GetBackwardsEdges()
{
	return m_edges;
}

void
BitmapContainer::AddHypothesis(Hypothesis *hypothesis)
{
	m_hypotheses.insert(hypothesis);
}

void
BitmapContainer::AddBackwardsEdge(BackwardsEdge *edge)
{
	m_edges.insert(edge);
}

void
BitmapContainer::PruneHypotheses()
{
	// NOT IMPLEMENTED YET.
}