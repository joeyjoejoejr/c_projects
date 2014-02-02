class Stack
  def initialize(opts = {})
    self.stack = []
    self.size = opts.fetch(:size) { 512 }
  end

  def peek
    stack[-1]
  end

  def pop
    stack.pop
  end

  def push(object)
    raise "Stack OverFlow" if count == size
    stack << object
  end

  def count
    stack.count
  end

  private
    attr_accessor :stack, :size
end

describe Stack do
  it "can push an object to the stack" do
    expect{ subject.push double("object") }
      .to change { subject.count }.from(0).to 1
  end

  it "can pop an object off the stack" do
    object = double("object")
    subject.push object
    expect(subject.pop).to be object
  end

  it "can peek at the object" do
    object = double("object")
    subject.push object
    expect {
      expect(subject.peek).to be object
    }.not_to change { subject.count }
  end

  it "raised an error on stack overflow" do
    stack = Stack.new(size: 1)
    stack.push double("object")
    expect {
      stack.push double("second object")
    }.to raise_error
  end
end
