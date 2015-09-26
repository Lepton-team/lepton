/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
#ifndef DECODER_HH
#define DECODER_HH
template<bool has_left, bool has_above, bool has_above_right, BlockType color>
void parse_tokens(BlockContext context,
                  Sirikata::Array1d<BoolDecoder,4>::Slice data,
                  ProbabilityTables<has_left, has_above, has_above_right, color> & probability_tables, ProbabilityTablesBase&pt);


#endif
